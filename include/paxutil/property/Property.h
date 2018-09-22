//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTY_H
#define PAXENGINE3_PROPERTY_H

#include "../reflection/TypeHandle.h"
#include "PropertyDependencies.h"

namespace PAX {
    template<class C>
    class PropertyContainer;

    template<class C>
    class Property {
        friend class PropertyContainer<C>;

    public:
        typedef C Container;

        static constexpr bool IsMultiple() { return true; }

    private:
        Container* owner = nullptr;

    protected:
        virtual const TypeHandle& getClassType() const = 0;

        virtual void attached(Container &) {}
        virtual void detached(Container &) {}

        virtual bool areDependenciesMetFor(const Container&) const { return true; }

    public:
        Property() : owner(nullptr) {}
        virtual ~Property() = default;

        Container* getOwner() const { return owner; }

        virtual bool isMultiple() const { return IsMultiple(); }
    };
}

#define PAX_PROPERTY_BODY(Parent, bool_multiple) \
private: \
    typedef Parent Super;\
protected: \
    virtual const TypeHandle& getClassType() const override { \
        static TypeHandle myType = typeid(*this); \
        return myType; \
    } \
public: \
    static constexpr bool IsMultiple() { return Super::IsMultiple() && (bool_multiple); } \
    virtual bool isMultiple() const override { return IsMultiple(); } \
private:

#define PAX_PROPERTY_DEPENDS_ON(...) \
protected: \
    virtual bool areDependenciesMetFor(const Container& container) const override { \
        static PAX::PropertyDependencies<Container, __VA_ARGS__> dependencies; \
        return Super::areDependenciesMetFor(container) && dependencies.met(container); \
    } \
private:

#endif //PAXENGINE3_PROPERTY_H
