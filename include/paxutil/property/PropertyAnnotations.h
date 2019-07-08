//
// Created by paul on 30.12.18.
//

#ifndef PAXENGINE3_PROPERTYANNOTATIONS_H
#define PAXENGINE3_PROPERTYANNOTATIONS_H

#include "PropertyDependencies.h"
#include "event/PropertyAttachedEvent.h"
#include "event/PropertyDetachedEvent.h"

/// Generators

//#define ENABLE_PROPERTY_CREATE_BY_NAME

// TODO: Find a way to make add and remove methods in PropertyContainer private.
#define PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, methodName, asMultiple, asSingle, EventType) \
bool Type::methodName(Container& c) { \
    if (Super::methodName(c)) { \
        PAX_CONSTEXPR_IF (This::IsMultiple()) { \
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

///// Annotations
#define PAX_PROPERTY_IS_ABSTRACT(...)
#define PAX_PROPERTY_IS_CONCRETE(...) __VA_ARGS__

/// Mandatory
#define PAX_PROPERTY(Typename, IfConcrete) \
public: \
    const ::PAX::TypeHandle& getClassType() const override; \
    static constexpr bool IsAbstract() { return IfConcrete(false &&) true; } \
protected: \
    using This = Typename; \
    bool addTo(Container& c) override; \
    bool removeFrom(Container& c) override; \
    void initializeFromProvider(::PAX::ContentProvider&) override; \
private: IfConcrete( \
/*    static ::PAX::PropertyFactory<This, Container> __ByNameFactory;*/ \
public: \
    static This * createFromProvider(::PAX::ContentProvider&); \
    static void* operator new(std::size_t sz); \
    static void operator delete(void * object); \
private: \
)

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
        static ::PAX::PropertyDependencies<Container, __VA_ARGS__> dependencies; \
        return Super::areDependenciesMetFor(container) && dependencies.met(container); \
    } \
private:

///// SOURCE

#define PAX_PROPERTY_SOURCE(Type, IfConcrete) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, addTo, addAsMultiple, addAsSingle, ::PAX::PropertyAttachedEvent) \
    PAX_GENERATE_PROPERTY_ADD_OR_REMOVE_SOURCE(Type, removeFrom, removeAsMultiple, removeAsSingle, ::PAX::PropertyDetachedEvent) \
    const ::PAX::TypeHandle& Type::getClassType() const { \
        static PAX::TypeHandle myType = typeid(This); \
        return myType; \
    } IfConcrete( \
/*    ::PAX::PropertyFactory<Type, Type::Container> Type::__ByNameFactory(#Type);*/ \
    void* Type::operator new(std::size_t sz) { \
        return Container::GetPropertyAllocator().alloc(paxtypeid(This), sz); \
    } \
    void Type::operator delete(void * object) { \
        Container::GetPropertyAllocator().free(paxtypeid(This), object); \
    })

#endif //PAXENGINE3_PROPERTYANNOTATIONS_H
