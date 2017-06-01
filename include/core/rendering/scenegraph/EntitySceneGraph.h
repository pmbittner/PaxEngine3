//
// Created by Paul on 28.05.2017.
//

#ifndef PAXENGINE3_ENTITYSCENEGRAPH_H
#define PAXENGINE3_ENTITYSCENEGRAPH_H

#include "SceneGraph.h"

namespace PAX {
    class EntitySceneGraph : public SceneGraph {
        Entity *_entity = nullptr;

    public:
        EntitySceneGraph(Entity *entity);

        Entity* getEntity();
        void setEntity(Entity *entity);
        virtual float getZ() override;
    };
}

#endif //PAXENGINE3_ENTITYSCENEGRAPH_H
