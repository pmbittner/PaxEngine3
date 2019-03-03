//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include <unordered_set>
#include <unordered_map>

#include <exception>

#include <utility> // std::forward

#include <paxutil/reflection/TypeMap.h>
#include <paxutil/stdutils/CollectionUtils.h>
#include <easylogging++.h>

#include "ResourceLoader.h"
#include "ResourceHandle.h"
#include "paxutil/io/Path.h"

namespace PAX {
    class ResourceAlreadyCachedException : public std::exception {
        std::string msg;

    public:
        explicit ResourceAlreadyCachedException(const std::string& res) {
            msg = std::string("The Resource ") + res + std::string(" is already cached!");
        }

        const char* what() const noexcept override
        {
            return msg.c_str();
        }
    };

    class Resources {
        TypeMap<std::vector<IResourceLoader*>> _loaders;
        TypeMap<std::unordered_set<ResourceHandle*>> _resourcesInUse;

        template<typename Resource, typename... Params>
        std::string print(Params... params) {
            std::stringstream ss;
            ss << Reflection::GetTypeName<Resource>() << "(" << Signature<Params...>(std::forward<Params>(params)...).toString() << ")";
            return ss.str();
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* getHandle(Params... p) {
            //std::cout << "[Resources::getHandle] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            Signature<Params...> s(p...);

            std::unordered_set<ResourceHandle*> &handles = _resourcesInUse[paxtypeof(Resource)];
            for (ResourceHandle *handle : handles) {
                if (s.equals(handle->_signature)) {
                    return reinterpret_cast<TypedResourceHandle<Resource>*>(handle);
                }
            }

            return nullptr;
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* registerResource(const std::shared_ptr<Resource> &res, ResourceLoader<Resource, Params...> *loader, Params... p) {
            //std::cout << "[Resources::registerResource] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            // TODO: Avoid these two "new" statements with custom allocators! Much new! Much slow!
            auto* handle = new TypedResourceHandle<Resource>();
            handle->_signature = new Signature<Params...>(p...);
            handle->_loader = loader;
            handle->_resource = res;

            _resourcesInUse[paxtypeof(Resource)].insert(handle);

            return handle;
        }

        bool unregisterResource(const std::type_index type, ResourceHandle* handle) {
            auto deletedElementCount = _resourcesInUse.at(type).erase(handle);
            delete handle; // deletes its signature
            return deletedElementCount > 0;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> loadResource(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader)
                return loader->load(p...);
            else
                LOG(WARNING) << "[Resources::loadResource] No ResourceLoader could be found for Resource " << print<Resource>(p...) << "!";
            return nullptr;
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* loadAndRegisterResource(Params... p) {
            //std::cout << "[Resources::loadAndRegisterResource] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader) {
                return registerResource<Resource, Params...>(
                        loader->load(p...),
                        loader,
                        p...);
            }
            return nullptr;
        }

    public:
        template<typename Resource>
        void registerLoader(ResourceLoaderT<Resource>* loader) {
            _loaders[paxtypeof(Resource)].push_back(loader);
        }

        template<typename Resource, typename... Params>
        ResourceLoader<Resource, Params...>* getLoader(Params... params) {
            std::vector<IResourceLoader *> &possibleLoaders = _loaders[paxtypeof(Resource)];
            for (IResourceLoader *possibleLoader : possibleLoaders) {
                auto *loader = dynamic_cast<ResourceLoader<Resource, Params...> *>(possibleLoader);
                if (loader) {
                    if (loader->canLoad(std::forward<Params>(params)...)) {
                        return loader;
                    }
                }
            }

            return nullptr;
        }

        /**
         * Tries to get the resource with the given parameters from the cache.
         * If this fails, the resource will be loaded and cached.
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& loadOrGet(Params... p) {
            //std::cout << "[Resources::loadOrGet] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            std::shared_ptr<Resource> &res = get<Resource>(p...);
            if (!res)
                return loadAndRegisterResource<Resource>(p...)->_resource;
            return res;
        }

        /**
         * Loads the resource of the given Type with the given parameters. This will only succeed if a
         * ResourceLoader is registered for this type, that can load the given signature. The resulting resource
         * will NOT be cached and already cached resources for this type and signature will be ignored!
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> load(Params... p) {
            std::shared_ptr<Resource> res = loadResource<Resource>(p...);

            if (!res)
                LOG(WARNING) << "[Resources::loadResource] The Resource " << print<Resource>(p...) << " could not be loaded!";

            return res;
        }

        /**
         * @return The resource, that is cached for the given parameters. Returns nullptr, if no resource is cached.
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& get(Params... p) {
            //std::cout << "[Resources::get_withCorrectPaths] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            TypedResourceHandle<Resource> *handle = getHandle<Resource, Params...>(p...);
            if (handle) {
                return handle->_resource;
            }

            static std::shared_ptr<Resource> shared_nullptr = std::shared_ptr<Resource>();
            return shared_nullptr;
        }

        /**
         * Loads the resource of the given Type with the given parameters. This will only succeed if a
         * ResourceLoader is registered for this type, that can load the given signature. The resulting resource
         * will then be cached if there is not a resource cached for this type already. In this case a
         * ResourceAlreadyCachedException will be thrown!
         * @return True, when the resource was loaded correctly.
         */
        template<typename Resource, typename... Params>
        bool cache(Params... p) {
            if (get<Resource>(p...))
                throw ResourceAlreadyCachedException(print<Resource>(p...));
            return loadAndRegisterResource<Resource>(p...) != nullptr;
        }

        void collectGarbage() {
            for (std::pair<const std::type_index, std::unordered_set<ResourceHandle*>> &kv : _resourcesInUse) {
                std::unordered_set<ResourceHandle*> &handles = kv.second;
                std::unordered_set<ResourceHandle*> resourcesToDelete;

                for (ResourceHandle* handle : handles) {
                    if (handle->getExternalReferenceCount() == 0) {
                        resourcesToDelete.insert(handle);
                    }
                }

                for (ResourceHandle* handle : resourcesToDelete) {
                    unregisterResource(kv.first, handle);
                }
            }
        }
    };
}

#endif //PAXENGINE3_RESOURCES_H