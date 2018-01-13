//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

//#include <typeindex>

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

#define PAX_EntityComponentDirect(Type, bool_multiple, ...) \
class Type; \
template<> \
struct EntityComponentProperties<Type> { \
    PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
    PAX::EntityComponentProperties<PAX::EntityComponent> parentProperties; \
    PAX::EntityComponent* cast(Type* component) const { return reinterpret_cast<PAX::EntityComponent*>(component); } \
    static constexpr bool IsMultiple() { return bool_multiple; } \
    PAX_EntityComponentProperties_DebugInfo \
};

#define PAX_EntityComponentSub(Type, Parent, ...) \
class Type; \
template<> \
struct EntityComponentProperties<Type> : EntityComponentProperties<Parent> { \
    PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
    PAX::EntityComponentProperties<Parent> parentProperties; \
    Parent* cast(Type* component) const { return reinterpret_cast<Parent*>(component); } \
    static constexpr bool IsMultiple() { return PAX::EntityComponentProperties<Parent>::IsMultiple(); } \
    PAX_EntityComponentProperties_DebugInfo \
};

//std::type_index parentType = std::type_index(typeid(Parent));
#endif //PAXENGINE3_ENTITYCOMPONENT_H
