//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTY_H
#define PAXENGINE3_PROPERTY_H

#include <memory>
#include "../reflection/TypeHandle.h"
#include "PropertyAnnotations.h"

namespace PAX {
    template<class C>
    class PropertyContainer;

    template<class C>
    class Property {
        friend class PropertyContainer<C>;

    public:
        using Container = C;
        static constexpr bool IsMultiple() { return true; }

    private:
        C* owner = nullptr;

    protected:
        virtual const TypeHandle& getClassType() const = 0;

        virtual bool addTo(C& container) { return true; }
        virtual bool removeFrom(C& container) { return true; }

        virtual void attached(C &) {}
        virtual void detached(C &) {}

        virtual bool areDependenciesMetFor(const C&) const { return true; }

    public:
        Property() : owner(nullptr) {}
        virtual ~Property() = default;

        C* getOwner() const { return owner; }

        virtual bool isMultiple() const { return IsMultiple(); }
    };
}

#endif //PAXENGINE3_PROPERTY_H
