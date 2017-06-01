//
// Created by Paul on 26.05.2017.
//

#include "../../../../../include/core/rendering/scenegraph/rule/GroupByEntitySceneGraphBuildingRule.h"
#include "../../../../../include/core/entity/Entity.h"
#include "../../../../../include/core/rendering/Graphics.h"
#include "../../../../../include/core/rendering/scenegraph/SceneGraph.h"
#include "../../../../../include/core/rendering/scenegraph/EntitySceneGraph.h"

namespace PAX {
    SceneGraph* GroupByEntitySceneGraphBuildingRule::findNodeOf(Entity *entity) {
        if (entity->has<Graphics>()) {
            const std::vector<Graphics *> &graphicsComponents = entity->get<Graphics>();
            for (Graphics *g : graphicsComponents) {
                SceneGraph *sceneGraph = g->getSceneGraph();
                if (sceneGraph) {
                    return sceneGraph;
                }
            }
        }

        return nullptr;
    }

    SceneGraph* GroupByEntitySceneGraphBuildingRule::determineSceneGraphNodeFor(Entity *entity, SceneGraph *root) {
        SceneGraph *node = findNodeOf(entity);

        if (node == nullptr) {
            node = new EntitySceneGraph(entity);
            SceneGraph *parentNode = nullptr;

            // hook new node into existing SceneGraph
            Entity *parent = entity->getParent();
            while (parent) {
                if (parentNode = findNodeOf(parent))
                    break;
                parent = parent->getParent();
            }

            if (parentNode == nullptr)
                parentNode = root;

            parentNode->addChild(node);

            // check for already existing nodes of children and
            // not implemented
        }

        return node;
    }

    SceneGraph * GroupByEntitySceneGraphBuildingRule::determineSceneGraphNodeFor(Graphics *graphics, SceneGraph *root) {
        Entity *entity = graphics->getOwner();
        assert(entity);
        return determineSceneGraphNodeFor(entity, root);
    }
}