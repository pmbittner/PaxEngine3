//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCELOADER_H
#define PAXENGINE3_RESOURCELOADER_H

#include "Path.h"

namespace PAX {
    class IResourceLoader {
    public:
        virtual ~IResourceLoader() {}
    };

    template<typename Resource>
    class ResourceLoaderT : public IResourceLoader {
    public:
        virtual bool free(Resource *res) = 0;
    };

    template<typename Resource, typename... Params>
    class ResourceLoader : public ResourceLoaderT<Resource> {
    public:
        virtual bool canLoad(Params...) = 0;
        virtual Resource *load(Params...) = 0;
    };
}

#endif //PAXENGINE3_RESOURCELOADER_H
