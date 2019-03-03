//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCELOADER_H
#define PAXENGINE3_RESOURCELOADER_H

#include <memory>
// This is just for use in subclasses, where Path is needed almost every time.
#include "paxutil/io/Path.h"

namespace PAX {
    class IResourceLoader {
    public:
        virtual ~IResourceLoader() {}
    };

    template<typename Resource>
    class ResourceLoaderT : public IResourceLoader {
    };

    template<typename Resource, typename... Params>
    class ResourceLoader : public ResourceLoaderT<Resource> {
    public:
        virtual bool canLoad(Params...) const = 0;
        virtual std::shared_ptr<Resource> load(Params...) = 0;
    };
}

#endif //PAXENGINE3_RESOURCELOADER_H
