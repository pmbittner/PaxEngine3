//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCELOADER_H
#define PAXENGINE3_RESOURCELOADER_H

#include <memory>
#include <map>

#include "polypropylene/reflection/VariableRegister.h"

// This is just for use in subclasses, where Path is needed almost every time.
#include "polypropylene/io/Path.h"

namespace PAX {
    class Resources;

    class IResourceLoader {
        friend class Resources;
    public:
        virtual ~IResourceLoader() = 0;
    };

    template<typename Resource>
    class ResourceLoaderT : public virtual IResourceLoader {
        friend class Resources;
    protected:
        // FIXME: Remove these methods
        virtual std::shared_ptr<Resource> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters) = 0;
        std::shared_ptr<Resource> loadFromPath(const std::string & loaderName, Resources & resources, const VariableHierarchy & parameters);
    };

    template<typename Resource, typename... Params>
    class ResourceLoader : public virtual ResourceLoaderT<Resource> {
    public:
        PAX_NODISCARD virtual bool canLoad(Params...) const = 0;
        PAX_NODISCARD virtual std::shared_ptr<Resource> load(Params...) = 0;
    };
}

#include "Resources.h"

#endif //PAXENGINE3_RESOURCELOADER_H
