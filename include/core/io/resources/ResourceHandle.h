//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCEHANDLE_H
#define PAXENGINE3_RESOURCEHANDLE_H

#include <utility/Signature.h>
#include "ResourceLoader.h"

namespace PAX {
    class Resources;
    class ResourceHandle {
        friend class Resources;

        void* _resource = nullptr;
        size_t _resourceSize = 0;
        int _uses = 0;

        ISignature *_signature;
        IResourceLoader *_loader;

    public:
        ResourceHandle();
        ~ResourceHandle();

        bool operator==(const ResourceHandle& other) const;
    };
}

#endif //PAXENGINE3_RESOURCEHANDLE_H
