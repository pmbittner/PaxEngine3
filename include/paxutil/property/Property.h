//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTY_H
#define PAXENGINE3_PROPERTY_H

#include "../reflection/TypeHandle.h"
#include "../macros/Definitions.h"
#include "construction/PropertyFactory.h"

namespace PAX {
    template<class C>
    class PropertyContainer;
    class ContentProvider;

    template<class C>
    class Property {
        friend class PropertyContainer<C>;
        friend class IPropertyFactory<C>;

    public:
        using Container = C;
        static constexpr bool IsMultiple() { return true; }

    private:
        C* owner = nullptr;

    protected:
        virtual bool addTo(C& container) PAX_NON_CONST { return true; }
        virtual bool removeFrom(C& container) PAX_NON_CONST { return true; }

        virtual void attached(C &) {}
        virtual void detached(C &) {}

        virtual void initializeFromProvider(ContentProvider & provider) = 0;

    public:
        Property() : owner(nullptr) {}
        virtual ~Property() = default;

        C* getOwner() const { return owner; }

        virtual const TypeHandle& getClassType() const = 0;
        virtual bool isMultiple() const { return IsMultiple(); }
        virtual bool areDependenciesMetFor(const C&) const { return true; }
    };

    template<typename C>
    void Property<C>::initializeFromProvider(ContentProvider & provider) {}
}

#include "PropertyAnnotations.h"

#endif //PAXENGINE3_PROPERTY_H
