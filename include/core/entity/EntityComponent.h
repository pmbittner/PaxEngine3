//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <typeindex>

#include "EntityComponentDependency.h"
#include "EntityComponentProperties.h"

#include <utility/macros/BuildType.h>

#ifdef PAX_DEBUG
#define PAX_EntityComponentProperties_DebugInfo void DEBUG_INFO___EntityComponentProperties_Missing___Use_The_Macros_In_EntityComponentH_to_Annotate_Your_Components() {}
#else
#define PAX_EntityComponentProperties_DebugInfo
#endif

#define PAX_ENTITYCOMPONENT(Type, Parent, bool_multiple) \
class Type; \
template<> \
struct EntityComponentProperties<Type> { \
    static constexpr bool IsMultiple() { return bool_multiple; } \
};

namespace PAX {
    class Entity;

    PAX_ENTITYCOMPONENT(EntityComponent, void, true)
    class EntityComponent {
        friend class Entity;

    private:
        Entity *_owner = nullptr;

    protected:
        virtual const std::type_index& getClassType() const = 0;
        virtual bool checkDependenciesFor(const Entity* entity) const;

        virtual void attached(Entity *entity);
        virtual void detached(Entity *entity);

    public:
        EntityComponent();
        virtual ~EntityComponent();

        Entity* getOwner() const;
    };
}

#undef PAX_ENTITYCOMPONENT

#define PAX_ENTITYCOMPONENT(Type, Parent, bool_multiple) \
class Type; \
template<> \
struct EntityComponentProperties<Type> { \
    static constexpr bool IsMultiple() { return PAX::EntityComponentProperties<Parent>::IsMultiple() && bool_multiple; } \
    PAX_EntityComponentProperties_DebugInfo \
};

#define PAX_ENTITYCOMPONENT_BODY \
protected: \
    virtual const std::type_index& getClassType() const override { \
        static std::type_index myType = typeid(*this); \
        return myType; \
    } \
private:

#define PAX_ENTITYCOMPONENT_DEPENDS_ON(Parent, ...) \
protected: \
    virtual bool checkDependenciesFor(const Entity* entity) const override { \
        static PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
        return Parent::checkDependenciesFor(entity) && dependencies.met(entity); \
    } \
private:

#endif //PAXENGINE3_ENTITYCOMPONENT_H
