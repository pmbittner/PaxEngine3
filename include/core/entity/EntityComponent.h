//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

namespace PAX {
    class Entity;

    class EntityComponent {
        friend class Entity;

    private:
        Entity *_owner = nullptr;

    public:
        EntityComponent();
        Entity* getOwner();

        virtual bool isMultiple() = 0;
    };
}

#define PAX_EntityComponent(name, bool_multiple, inheritance...) class name : public PAX::EntityComponent, ##inheritance { \
            public: \
                const static bool IsMultiple = bool_multiple;\
                virtual bool isMultiple() override { return bool_multiple; } \
            private:

#endif //PAXENGINE3_ENTITYCOMPONENT_H
