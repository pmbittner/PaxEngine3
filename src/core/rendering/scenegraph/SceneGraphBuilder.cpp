//
// Created by Paul on 08.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraphBuilder.h"
#include <vector>

namespace PAX {
    void SceneGraphBuilder::initialize() {

    }

    void SceneGraphBuilder::addGraphics(Graphics *g) {

    }

    void SceneGraphBuilder::removeGraphics(Graphics *g) {

    }

    void SceneGraphBuilder::onEvent(EntitySpawnedEvent *e) {
        Entity *entity = e->entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*>* gfx = entity->get<Graphics>();
            for (Graphics *g : *gfx)
                addGraphics(g);
        }
    }

    void SceneGraphBuilder::onEvent(EntityComponentAddedEvent<Graphics> *e) {
        addGraphics(e->_component);
    }

    void SceneGraphBuilder::onEvent(EntityDespawnedEvent *e) {
        Entity *entity = e->entity;
        if (entity->has<Graphics>()) {
            const std::vector<Graphics*>* gfx = entity->get<Graphics>();
            for (Graphics *g : *gfx)
                removeGraphics(g);
        }
    }

    void SceneGraphBuilder::onEvent(EntityComponentRemovedEvent<Graphics> *e) {
        removeGraphics(e->_component);
    }
}