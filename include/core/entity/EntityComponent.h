//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include "../../utility/Dependency.h"

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
        virtual const Dependency<Entity>* getDependency();
        virtual bool isMultiple() = 0;
    };
}

#define PAX_EntityComponent(name, bool_multiple, ...) class name : public PAX::EntityComponent, ##__VA_ARGS__ { \
            public: \
                static constexpr bool IsMultiple() { return bool_multiple; } \
                virtual bool isMultiple() override { return bool_multiple; } \
            private:

#define PAX_EntityComponent_DependsOn(...) \
            public: \
                virtual const Dependency<Entity>* getDependency() override { \
                    static EntityComponentDependency<__VA_ARGS__> Dependencies; \
                    return &Dependencies; \
                } \
            private:

#endif //PAXENGINE3_ENTITYCOMPONENT_H
