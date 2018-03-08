//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include <unordered_set>
#include <unordered_map>

#include <exception>

#include <utility/datastructures/TypeMap.h>
#include <utility/stdutils/CollectionUtils.h>
#include <easylogging++.h>

#include "ResourceLoader.h"
#include "ResourceHandle.h"

namespace PAX {
    template<typename T> struct convert {
        using type = T;
    };
    template<> struct convert<char const*> {
        using type = Path;
    };
    template<> struct convert<std::string> {
        using type = Path;
    };
    template<typename T>
    using convertStringsToPath = typename convert<T>::type;

    class ResourceAlreadyCachedException : public std::exception
    {
        std::string msg;

    public:
        ResourceAlreadyCachedException(const std::string& res) {
            msg = std::string("The Resource ") + res + std::string(" is already cached!");
        }

        virtual const char* what() const throw()
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
            ss << Reflection::GetTypeName<Resource>() << "(" << Signature<Params...>(params...).toString() << ")";
            return ss.str();
        }

        template<typename Resource, typename... Params>
        ResourceLoader<Resource, Params...>* getLoader(Params... params) {
            std::vector<IResourceLoader *> &possibleLoaders = _loaders.get<Resource>();
            for (IResourceLoader *possibleLoader : possibleLoaders) {
                ResourceLoader<Resource, Params...> *loader = dynamic_cast<ResourceLoader<Resource, Params...> *>(possibleLoader);
                if (loader) {
                    if (loader->canLoad(params...)) {
                        return loader;
                    }
                }
            }

            return nullptr;
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* getHandle(Params... params) {
            Signature<Params...> s(params...);

            std::unordered_set<ResourceHandle*> &handles = _resourcesInUse.get<Resource>();
            for (ResourceHandle *handle : handles) {
                if (s.equals(handle->_signature)) {
                    return reinterpret_cast<TypedResourceHandle<Resource>*>(handle);
                }
            }

            return nullptr;
        }

        template<typename Resource, typename... Params>
        inline std::shared_ptr<Resource> createSharedPointerFor(Resource *res, ResourceLoader<Resource, Params...> *loader) {
            return std::shared_ptr<Resource>(res, /*deleter*/
                                      [loader](Resource* r) {
                                          loader->free(r);
                                      });
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* registerResource(Resource *res, ResourceLoader<Resource, Params...> *loader, Params... params) {
            // TODO: Avoid these two "new" statements with custom allocators! Much allocation! Much new! Much slow!
            TypedResourceHandle<Resource>* handle = new TypedResourceHandle<Resource>();
            handle->_signature = new Signature<Params...>(params...);
            handle->_loader = loader;
            handle->_resource = createSharedPointerFor(res, loader);

            _resourcesInUse.get<Resource>().insert(handle);

            return handle;
        }

        bool unregisterResource(const std::type_index type, ResourceHandle* handle) {
            auto deletedElementCount = _resourcesInUse.get(type).erase(handle);
            delete handle;
            return deletedElementCount;
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* loadAndRegisterResource(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader) {
                return registerResource<Resource, Params...>(
                        loader->load(p...),
                        loader,
                        p...);
            }
            return nullptr;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> loadResource(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader)
                return createSharedPointerFor(loader->load(p...), loader);
            return nullptr;
        }


    private: ////////////////// The Internal functions for automatic string replacement: string -> path /////////////////////////////

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& get_withCorrectPaths(Params... p) {
            TypedResourceHandle<Resource> *handle = getHandle<Resource, Params...>(p...);
            if (handle) {
                return handle->_resource;
            }

            static std::shared_ptr<Resource> shared_nullptr = std::shared_ptr<Resource>();
            return shared_nullptr;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> load_withCorrectPaths(Params... p) {
            std::shared_ptr<Resource> res = loadResource<Resource>(p...);

            if (res)
                return res;
            else
                LOG(WARNING) << "The Resource " << print<Resource>(p...) << " could not be loaded!";

            static std::shared_ptr<Resource> shared_nullptr = std::shared_ptr<Resource>();
            return shared_nullptr;
        }

        template<typename Resource, typename... Params>
        bool cache_withCorrectPaths(Params... p) {
            std::shared_ptr<Resource> &res = get_withCorrectPaths<Resource>(p...);
            if (res)
                throw ResourceAlreadyCachedException(print<Resource>(p...));
            return loadAndRegisterResource<Resource>(p...) != nullptr;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& loadOrGet_withCorrectPaths(Params... p) {
            std::shared_ptr<Resource> &res = get_withCorrectPaths<Resource>(p...);
            if (!res)
                return loadAndRegisterResource<Resource>(p...)->_resource;
            return res;
        }

    public:
        template<typename Resource, typename... Params>
        void registerLoader(ResourceLoader<Resource, Params...>* loader) {
            std::vector<IResourceLoader*> &loaders = _loaders.get<Resource>();
            loaders.push_back(loader);
        }

        /**
         * @return The resource, that is cached for the given parameters. Returns nullptr, if no resource is cached.
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& get(Params... p) {
            return get_withCorrectPaths<Resource, convertStringsToPath<Params>...>(p...);
        }

        /**
         * Loads the resource of the given Type with the given parameters. This will only succeed if a
         * ResourceLoader is registered for this type, that can load the given signature. The resulting resource
         * will NOT be cached and already cached resources for this type and signature will be ignored!
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource> load(Params... p) {
            return load_withCorrectPaths<Resource, convertStringsToPath<Params>...>(p...);
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
            return cache_withCorrectPaths<Resource, convertStringsToPath<Params>...>(p...);
        }

        /**
         * Tries to get the resource with the given parameters from the cache. If this fails, the resource will be loaded
         */
        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& loadOrGet(Params... p) {
            return loadOrGet_withCorrectPaths<Resource, convertStringsToPath<Params>...>(p...);
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
