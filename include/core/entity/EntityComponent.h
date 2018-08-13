//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <typeindex>
#include "EntityComponentDependency.h"

namespace PAX {
    class Entity;
    class EntityComponent;

    class EntityComponent {
        friend class Entity;

    public:
        static constexpr bool IsMultiple() { return true; }

    private:
        Entity *_owner = nullptr;

    protected:
        virtual const std::type_index& getClassType() const = 0;

        virtual void attached(Entity *entity);
        virtual void detached(Entity *entity);

        virtual bool areDependenciesMetFor(const Entity* entity) const;

    public:
        EntityComponent();
        virtual ~EntityComponent();

        Entity* getOwner() const;

        virtual bool isMultiple() const;
    };
}

#define PAX_ENTITYCOMPONENT_BODY(Parent, bool_multiple) \
private: \
    typedef Parent Super;\
protected: \
    virtual const std::type_index& getClassType() const override { \
        static std::type_index myType = typeid(*this); \
        return myType; \
    } \
public: \
    static constexpr bool IsMultiple() { return Super::IsMultiple() && (bool_multiple); } \
    virtual bool isMultiple() const override { return IsMultiple(); } \
private:

#define PAX_ENTITYCOMPONENT_DEPENDS_ON(...) \
protected: \
    virtual bool areDependenciesMetFor(const Entity* entity) const override { \
        static PAX::EntityComponentDependency<__VA_ARGS__> dependencies; \
        return Super::areDependenciesMetFor(entity) && dependencies.met(entity); \
    } \
private:

#endif //PAXENGINE3_ENTITYCOMPONENT_H
