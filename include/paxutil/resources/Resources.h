//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include <unordered_set>
#include <unordered_map>

#include <exception>

#include <utility> // std::forward

#include <polypropylene/reflection/TypeMap.h>
#include <polypropylene/stdutils/CollectionUtils.h>
#include <polypropylene/reflection/VariableRegister.h>

#include "ResourceLoader.h"
#include "ResourceHandle.h"

#include <polypropylene/io/Path.h>
#include <polypropylene/log/Errors.h>

namespace PAX {
    class ResourceAlreadyCachedException : public std::exception {
        std::string msg;

    public:
        explicit ResourceAlreadyCachedException(const std::string& res);
        const char* what() const noexcept override;
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

            std::unordered_set<ResourceHandle*> &handles = _resourcesInUse[paxtypeid(Resource)];
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

            _resourcesInUse[paxtypeid(Resource)].insert(handle);

            return handle;
        }

        bool unregisterResource(const std::type_index type, ResourceHandle* handle);

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> loadResource(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader)
                return loader->load(p...);
            else
                PAX_LOG(Log::Level::Warn, "[Resources::loadResource] No ResourceLoader could be found for Resource " << print<Resource>(p...) << "!");
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
            _loaders[paxtypeid(Resource)].push_back(loader);
        }

        template<typename Resource>
        const std::vector<ResourceLoaderT<Resource>*> & getLoaders() {
            std::vector<IResourceLoader *> &loaders = _loaders[paxtypeid(Resource)];
            return *reinterpret_cast<std::vector<ResourceLoaderT<Resource>*>*>(&loaders);
        }

        template<typename Resource, typename... Params>
        ResourceLoader<Resource, Params...>* getLoader(Params... params) {
            std::vector<IResourceLoader *> &possibleLoaders = _loaders[paxtypeid(Resource)];
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
        std::shared_ptr<Resource> loadOrGet(Params... p) {
            //std::cout << "[Resources::loadOrGet] " << print<Resource, Params...>(p...) << std::endl << std::endl;
            std::shared_ptr<Resource> &res = get<Resource>(p...);
            if (!res) {
                auto * handle = loadAndRegisterResource<Resource>(p...);

                if (!handle) {
                    PAX_THROW_RUNTIME_ERROR("[Resources::loadOrGet<" << print<Resource, Params...>(p...) << ">] FAILED: Resource could neither be found nor loaded!");
                }

                return handle->_resource;
            }
            return res;
        }

        template<typename Resource>
        std::shared_ptr<Resource> loadOrGetFromVariableRegister(const VariableHierarchy & vars) {
            const auto & loaders = getLoaders<Resource>();

            for (ResourceLoaderT<Resource> * loader : loaders) {
                if (auto res = loader->loadToOrGetFromResources(*this, vars))
                    return res;
            }

            return nullptr;
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
                PAX_LOG(Log::Level::Warn, "[Resources::loadResource] The Resource " << print<Resource>(p...) << " could not be loaded!");

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

            static std::shared_ptr<Resource> shared_nullptr = nullptr;
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

        void collectGarbage();
    };

    template<typename Resource>
    std::shared_ptr<Resource> ResourceLoaderT<Resource>::loadFromPath(const std::string & loaderName, Resources & resources, const VariableHierarchy & parameters) {
        // Only one entry is required, namely the Path
        if (parameters.values.size() == 1) {
            const std::string & key = parameters.values.begin()->first;
            if (!key.empty()) {
                return resources.loadOrGet<Resource>(Path(key));
            }
            const std::string & value = parameters.values.begin()->second;
            if (!value.empty()) {
                return resources.loadOrGet<Resource>(Path(value));
            }
        }

        PAX_LOG(Log::Level::Error, "[" << loaderName << "::loadToOrGetFromResources] Could not obtain path from parameters!");

        return nullptr;
    }
}

#endif //PAXENGINE3_RESOURCES_H
