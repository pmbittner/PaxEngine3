//
// Created by Paul on 28.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/EntitySceneGraph.h"

namespace PAX {
    EntitySceneGraph::EntitySceneGraph(Entity *entity) : SceneGraph() {
        setEntity(entity);
    }

    float EntitySceneGraph::getZ() {
        return _entity->getTransform().z();
    }

    Entity* EntitySceneGraph::getEntity() {
        return _entity;
    }

    void EntitySceneGraph::setEntity(Entity *entity) {
        _entity = entity;
    }
}