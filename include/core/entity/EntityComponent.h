//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <typeindex>

#include "EntityComponentDependency.h"
#include "EntityComponentProperties.h"

#include <utility/macros/BuildType.h>

namespace PAX {
    class Entity;

    class EntityComponent {
        friend class Entity;

    private:
        Entity *_owner = nullptr;

    protected:
        virtual const std::type_index& GetClassType() = 0;

        virtual void attached(Entity *entity);
        virtual void detached(Entity *entity);

    public:
        EntityComponent();
        virtual ~EntityComponent();

        Entity* getOwner();
    };

}

#ifdef PAX_DEBUG
#define PAX_EntityComponentProperties_DebugInfo void DEBUG_INFO___EntityComponentProperties_Missing___Use_The_Macros_In_EntityComponentH_to_Annotate_Your_Components() {}
#else
#define PAX_EntityComponentProperties_DebugInfo
#endif

#define PAX_ENTITYCOMPONENT(Type, bool_multiple, ...) \
class Type; \
template<> \
struct EntityComponentProperties<Type> { \
    PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
    std::type_index parentType = typeid(PAX::EntityComponent); \
    PAX::EntityComponentProperties<PAX::EntityComponent> parentProperties; \
    PAX::EntityComponent* cast(Type* component) const { return reinterpret_cast<PAX::EntityComponent*>(component); } \
    static constexpr bool IsMultiple() { return bool_multiple; } \
    PAX_EntityComponentProperties_DebugInfo \
};

#define PAX_ENTITYCOMPONENT_DERIVED(Type, Parent, ...) \
class Type; \
template<> \
struct EntityComponentProperties<Type> : EntityComponentProperties<Parent> { \
    PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
    std::type_index parentType = typeid(Parent); \
    PAX::EntityComponentProperties<Parent> parentProperties; \
    Parent* cast(Type* component) const { return reinterpret_cast<Parent*>(component); } \
    static constexpr bool IsMultiple() { return PAX::EntityComponentProperties<Parent>::IsMultiple(); } \
    PAX_EntityComponentProperties_DebugInfo \
};

// to gain complete independence from templates add line, which sadly requires the Type
// virtual bool isMultiple() override { return EntityComponentProperties<Type>::IsMultiple(); }

// Additionally the complete annotation struct may be useless then, as only get() and has() have to be template at all!
// In this case using the Type as single argument may be valid. Dependencies could be another extra macro once again

#define PAX_ENTITYCOMPONENT_BODY \
protected: \
    virtual const std::type_index& GetClassType() override { \
        static std::type_index MyType = typeid(*this); \
        return MyType; \
    } \
private:

#endif //PAXENGINE3_ENTITYCOMPONENT_H
