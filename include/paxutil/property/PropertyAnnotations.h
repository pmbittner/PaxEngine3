//
// Created by paul on 30.12.18.
//

#ifndef PAXENGINE3_PROPERTYANNOTATIONS_H
#define PAXENGINE3_PROPERTYANNOTATIONS_H

#include "PropertyDependencies.h"
#include "PropertyFactory.h"
#include "event/PropertyAttachedEvent.h"
#include "event/PropertyDetachedEvent.h"

/// Generators

//#define ENABLE_PROPERTY_CREATE_BY_NAME

// TODO: Find a way to make add and remove methods in PropertyContainer private.
#define PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, methodName, asMultiple, asSingle, EventType) \
bool Type::methodName(Container& c) { \
    if (Super::methodName(c)) { \
        if constexpr (This::IsMultiple()) { \
            if (!c.asMultiple(paxtypeid(This), this)) return false; \
        } else { \
            if (!c.asSingle(paxtypeid(This), this)) return false; \
        } \
        EventType<Container, This> event(this, &c); \
        c.getEventService()(event); \
        return true; \
    } \
    return false; \
}

#ifdef ENABLE_PROPERTY_CREATE_BY_NAME
    #define PAX_GENERATE_CREATE_BY_NAME_HEADER static PAX::PropertyRegister<This, Container> PropertyNameRegister;
    #define PAX_GENERATE_CREATE_BY_NAME_SOURCE(Type) PAX::PropertyRegister<Type, Type::Container> Type::PropertyNameRegister(#Type);
#else
    #define PAX_GENERATE_CREATE_BY_NAME_HEADER
    #define PAX_GENERATE_CREATE_BY_NAME_SOURCE(Type)
#endif

///// Annotations

/// Mandatory
#define PAX_PROPERTY(Typename) \
protected: \
    using This = Typename; \
    const PAX::TypeHandle& getClassType() const override; \
    bool addTo(Container& c) override; \
    bool removeFrom(Container& c) override; \
private: \
    PAX_GENERATE_CREATE_BY_NAME_HEADER

#define PAX_PROPERTY_DERIVES(Parent) \
public: \
    using Super = Parent; \
private:

#define PAX_PROPERTY_SETMULTIPLE(bool_val) \
public:\
    static constexpr bool IsMultiple() { return Super::IsMultiple() && (bool_val); } \
    bool isMultiple() const override { return IsMultiple(); } \
private:

#define PAX_PROPERTY_IS_MULTIPLE PAX_PROPERTY_SETMULTIPLE(true)
#define PAX_PROPERTY_IS_SINGLE PAX_PROPERTY_SETMULTIPLE(false)

/// Optional

#define PAX_PROPERTY_DEPENDS_ON(...) \
protected: \
    virtual bool areDependenciesMetFor(const Container& container) const override { \
        static PAX::PropertyDependencies<Container, __VA_ARGS__> dependencies; \
        return Super::areDependenciesMetFor(container) && dependencies.met(container); \
    } \
private:

///// SOURCE

#define PAX_PROPERTY_SOURCE(Type) \
    PAX_GENERATE_CREATE_BY_NAME_SOURCE(Type) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, addTo, addAsMultiple, addAsSingle, PAX::PropertyAttachedEvent) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, removeFrom, removeAsMultiple, removeAsSingle, PAX::PropertyDetachedEvent) \
    const PAX::TypeHandle& Type::getClassType() const { \
        static PAX::TypeHandle myType = typeid(This); \
        return myType; \
    }

#endif //PAXENGINE3_PROPERTYANNOTATIONS_H
