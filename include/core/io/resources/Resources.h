//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include <vector>
#include <utility/datastructures/TypeMap.h>
#include <utility/stdutils.h>
#include <iostream>
#include <unordered_map>

#include "ResourceLoader.h"
#include "ResourceHandle.h"

namespace PAX {
    class Resources {
        TypeMap<std::vector<IResourceLoader*>> _loaders;

        TypeMap<std::vector<ResourceHandle>> _resourcesInUse;
        std::unordered_map<void*, ResourceHandle*> _resourceToHandle;

    private:
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

        template<typename Resource>
        ResourceHandle* getHandle(Resource *resource) {
            auto iterator = _resourceToHandle.find(resource);
            if (iterator != _resourceToHandle.end())
                return iterator->second;
            return nullptr;
        }

        template<typename Resource, typename... Params>
        ResourceHandle* getHandle(Params... params) {
            Signature<Params...> s(params...);

            std::vector<ResourceHandle> &handles = _resourcesInUse.get<Resource>();
            for (ResourceHandle &handle : handles) {
                if (handle._signature->equals(s)) {
                    return &handle;
                }
            }

            return nullptr;
        }

        template<typename Resource, typename... Params>
        ResourceHandle* registerResource(Resource *res, Params... params) {
            ResourceHandle* handle = getHandle<Resource>(res);

            if (!handle) {
                ResourceHandle newEntry;
                newEntry._signature = new Signature<Params...>(params...);
                newEntry._resource = res;
                newEntry._resourceSize = sizeof(Resource);

                std::vector<ResourceHandle> &handles = _resourcesInUse.get<Resource>();
                handles.push_back(newEntry);
                handle = &handles.back();

                _resourceToHandle[static_cast<void*>(res)] = handle;
            }

            return handle;
        }

        template<typename Resource>
        bool unregisterResource(Resource *res) {
            ResourceHandle* handle = getHandle<Resource>(res);

            if (handle) {
                Util::removeFromVector(_resourcesInUse.get<Resource>(), *handle);
                _resourceToHandle.erase(res);
                return true;
            }

            return false;
        }

        template<typename Resource, typename... Params>
        Resource* load(Params... p) {
            ResourceLoader<Resource, Params...> *loader = getLoader<Resource>(p...);
            if (loader) {
                Resource *r = loader->load(p...);
                ResourceHandle* handle = registerResource<Resource, Params...>(r, p...);
                handle->_loader = loader;
                handle->_uses = 1;
                return r;
            }
            return nullptr;
        }

    public:
        template<typename Resource, typename... Params>
        bool registerLoader(ResourceLoader<Resource, Params...>* loader) {
            std::vector<IResourceLoader*> &loaders = _loaders.get<Resource>();
            loaders.push_back(loader);
        }

        template<typename Resource, typename... Params>
        Resource* get(Params... p) {
            ResourceHandle *handle = getHandle<Resource, Params...>(p...);
            if (handle) {
                handle->_uses++;
                return static_cast<Resource*>(handle->_resource);
            }
            return nullptr;
        }

        template<typename Resource, typename... Params>
        Resource* loadOrGet(Params... p) {
            Resource* res = get<Resource>(p...);
            if (!res)
                res = load<Resource>(p...);
            return res;
        }

        template<typename Resource>
        bool free(Resource *resource) {
            ResourceHandle *handle = getHandle<Resource>(resource);

            if (handle) {
                handle->_uses--;

                if (handle->_uses == 0) {
                    ResourceLoaderT<Resource> *loader = static_cast<ResourceLoaderT<Resource>*>(handle->_loader);
                    if (loader->free(resource)) {
                        if (unregisterResource<Resource>(resource))
                            return true;
                    }
                }
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_RESOURCES_H
