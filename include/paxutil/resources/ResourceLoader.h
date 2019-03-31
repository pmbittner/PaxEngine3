//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCELOADER_H
#define PAXENGINE3_RESOURCELOADER_H

#include <memory>
#include <map>

#include "paxutil/StringVariables.h"

// This is just for use in subclasses, where Path is needed almost every time.
#include "paxutil/io/Path.h"

namespace PAX {
    class Resources;

    class IResourceLoader {
        friend class Resources;
    public:
        virtual ~IResourceLoader();
    };

    template<typename Resource>
    class ResourceLoaderT : public IResourceLoader {
        friend class Resources;
    protected:
        virtual std::shared_ptr<Resource> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters) = 0;
        std::shared_ptr<Resource> loadFromPath(const std::string & loaderName, Resources & resources, const VariableHierarchy & parameters);
    };

    template<typename Resource, typename... Params>
    class ResourceLoader : public ResourceLoaderT<Resource> {
    public:
        virtual bool canLoad(Params...) const = 0;
        virtual std::shared_ptr<Resource> load(Params...) = 0;
    };
}

#include "Resources.h"

#endif //PAXENGINE3_RESOURCELOADER_H
