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
    virtual bool isMultiple() const override { return IsMultiple(); } \
private:

#define PAX_GENERATE_PROPERTY_ADD_OR_REMOVE(MethodName, ContainerMethodName, EventType) \
bool MethodName(PropertyContainer<Container>& c, const std::shared_ptr<Property<Container>> & me) override { \
    using This  = std::remove_pointer<decltype(this)>::type; \
    if (Super::MethodName(c, me)) { \
        if (!c.ContainerMethodName(typeid(This), me)) return false; \
        auto event = EventType<Container, This>(std::dynamic_pointer_cast<This>(me), static_cast<Container*>(&c)); \
        c.getEventService()(event); \
        return true; \
    } \
    return false; \
}

/// Annotations

// TODO: avoid std::dynamic_pointer_cast
// TODO: Find a way to make add and remove methods in PropertyContainer private.

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
