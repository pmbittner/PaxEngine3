//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYER_H
#define PAXENGINE3_WORLDLAYER_H

#include <string>
#include <vector>
#include "WorldLayerLayout.h"
#include "../entity/Entity.h"

namespace PAX {

    class WorldLayer {
    private:
        std::string _name;
        WorldLayerLayout *_layout;
        float _z;

        std::vector<Entity*> _entities;

    public:
        WorldLayer(std::string name);

        void spawn(Entity *entity);
        void despawn(Entity *entity);

        std::string getName();
    };
}

#endif //PAXENGINE3_WORLDLAYER_H
