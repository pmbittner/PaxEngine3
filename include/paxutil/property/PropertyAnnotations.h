//
// Created by paul on 30.12.18.
//

#ifndef PAXENGINE3_PROPERTYANNOTATIONS_H
#define PAXENGINE3_PROPERTYANNOTATIONS_H

#include "PropertyDependencies.h"
#include "paxutil/property/event/PropertyAttachedEvent.h"
#include "paxutil/property/event/PropertyDetachedEvent.h"

/// Generators

#define PAX_GENERATE_PROPERTY_ISMULTIPLE(bool_val) \
public:\
    static constexpr bool IsMultiple() { return Super::IsMultiple() && (bool_val); } \
    bool isMultiple() const override { return IsMultiple(); } \
private:

#define PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(MethodName, ContainerMethodName, EventType) \
bool MethodName(Container& c) override { \
    if (Super::MethodName(c)) { \
        using This = std::remove_pointer<decltype(this)>::type; \
        if (!c.ContainerMethodName(typeid(This), this)) return false; \
        auto event = EventType<Container, This>(this, &c); \
        c.getEventService()(event); \
        return true; \
    } \
    return false; \
}

/// HEADER
#define PAX_GENERATE_PROPERTY_ADD_AND_REMOVE_HEADER() \
bool addTo(Container& c) override; \
bool removeFrom(Container& c) override;

/// SOURCE

#define PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE_SINGLE(Type) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(Type::addTo, addAsSingle, PAX::PropertyAttachedEvent) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(Type::removeFrom, removeAsSingle, PAX::PropertyDetachedEvent)

/// Annotations

// TODO: Find a way to make add and remove methods in PropertyContainer private.

#define PAX_PROPERTY_OPTIONAL(Typename, Container) \
private:\
    using This = Typename; \
    static PropertyRegister<This, Container> PropertyNameRegister;

#define PAX_PROPERTY_OPTIONAL_CPP(Typename, Container) \
    PropertyRegister<Typename, Container> Typename::PropertyNameRegister = PropertyRegister<Typename, Container>(#Typename);


#define PAX_PROPERTY_DERIVES(Parent) \
private: \
    using Super = Parent; \
protected: \
    const TypeHandle& getClassType() const override { \
        static TypeHandle myType = typeid(*this); \
        return myType; \
    } \
private:


#define PAX_PROPERTY_IS_SINGLE \
    PAX_GENERATE_PROPERTY_ISMULTIPLE(false) \
protected: \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(addTo, addAsSingle, PAX::PropertyAttachedEvent) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(removeFrom, removeAsSingle, PAX::PropertyDetachedEvent) \
private:


#define PAX_PROPERTY_IS_MULTIPLE \
    PAX_GENERATE_PROPERTY_ISMULTIPLE(true) \
protected: \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(addTo, addAsMultiple, PAX::PropertyAttachedEvent) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(removeFrom, removeAsMultiple, PAX::PropertyDetachedEvent) \
private:


#define PAX_PROPERTY_DEPENDS_ON(...) \
protected: \
    virtual bool areDependenciesMetFor(const Container& container) const override { \
        static PAX::PropertyDependencies<Container, __VA_ARGS__> dependencies; \
        return Super::areDependenciesMetFor(container) && dependencies.met(container); \
    } \
private:

#endif //PAXENGINE3_PROPERTYANNOTATIONS_H
