//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCEHANDLE_H
#define PAXENGINE3_RESOURCEHANDLE_H

#include <memory>
#include <string>

#include "ResourceLoader.h"

#include <paxutil/Signature.h>
#include <paxutil/reflection/TemplateTypeToString.h>

namespace PAX {
    class Resources;
    class ResourceHandle {
        friend class Resources;

        ISignature *_signature = nullptr;
        IResourceLoader *_loader = nullptr;

    public:
        ResourceHandle();
        virtual ~ResourceHandle();

        virtual int getExternalReferenceCount() const = 0;

        virtual std::string toString() {
            return _signature ? _signature->toString() : "";
        }
    };

    template<typename ResType>
    class TypedResourceHandle : ResourceHandle {
        friend class Resources;

    public:
        std::shared_ptr<ResType> _resource = nullptr;

        bool operator==(const TypedResourceHandle<ResType>& other) const {
            return _resource == other._resource;
        };

        virtual int getExternalReferenceCount() const override {
            return _resource.use_count() - 1; // subtract our own reference
        }

        virtual std::string toString() override {
            return std::string(Reflection::GetTypeName<ResType>()) + "(" + ResourceHandle::toString() + ")";
        }
    };
}

#endif //PAXENGINE3_RESOURCEHANDLE_H
