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
        Entity *_owner;

    public:
        EntityComponent();
        Entity* getOwner();
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENT_H
