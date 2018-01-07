//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include <unordered_set>
#include <unordered_map>

#include <utility/datastructures/TypeMap.h>
#include <utility/stdutils/CollectionUtils.h>
#include <lib/easylogging++.h>

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
        TypedResourceHandle<Resource>* registerResource(ResourceLoader<Resource, Params...> *loader, Params... params) {
            Resource *res = loader->load(params...);

            TypedResourceHandle<Resource>* handle = new TypedResourceHandle<Resource>();
            handle->_signature = new Signature<Params...>(params...);
            handle->_loader = loader;
            handle->_resource = std::shared_ptr<Resource>(res, /*deleter*/
                                                          [loader](Resource* r) {
                                                              loader->free(r);
                                                          });

            _resourcesInUse.get<Resource>().insert(handle);

            return handle;
        }

        bool unregisterResource(const std::type_index type, ResourceHandle* handle) {
            auto deletedElementCount = _resourcesInUse.get(type).erase(handle);
            delete handle;
            return deletedElementCount;
        }

        template<typename Resource, typename... Params>
        TypedResourceHandle<Resource>* load(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader) {
                return registerResource<Resource, Params...>(
                        loader,
                        p...);
            }
            return nullptr;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& get(Params... p) {
            TypedResourceHandle<Resource> *handle = getHandle<Resource, Params...>(p...);
            if (handle) {
                return handle->_resource;
            }

            static std::shared_ptr<Resource> shared_nullptr = std::shared_ptr<Resource>();
            return shared_nullptr;
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& loadOrGetWithCorrectPaths(Params... p) {
            std::shared_ptr<Resource> &res = get<Resource>(p...);
            if (!res) {
                TypedResourceHandle<Resource> *handle = load<Resource>(p...);
                if (handle)
                    return handle->_resource;
                else
                    LOG(WARNING) << "The Resource " << print<Resource>(p...) << " could not be loaded!";
            }
            return res;
        };

    public:
        template<typename Resource, typename... Params>
        void registerLoader(ResourceLoader<Resource, Params...>* loader) {
            std::vector<IResourceLoader*> &loaders = _loaders.get<Resource>();
            loaders.push_back(loader);
        }

        template<typename Resource, typename... Params>
        std::shared_ptr<Resource>& loadOrGet(Params... p) {
            return loadOrGetWithCorrectPaths<Resource, convertStringsToPath<Params>...>(p...);
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
