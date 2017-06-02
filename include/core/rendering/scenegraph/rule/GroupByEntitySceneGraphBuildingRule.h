//
// Created by Paul on 26.05.2017.
//

#ifndef PAXENGINE3_TREESCENEGRAPHBUILDINGRULE_H
#define PAXENGINE3_TREESCENEGRAPHBUILDINGRULE_H

#include "../SceneGraphBuildingRule.h"

namespace PAX {
    class Entity;
    class GroupByEntitySceneGraphBuildingRule : public SceneGraphBuildingRule {
        SceneGraph* findNodeOf(Entity *entity);
        SceneGraph* determineSceneGraphNodeFor(Entity *entity, SceneGraph* root);
    public:
        virtual SceneGraph* determineSceneGraphNodeFor(EntityComponent *component, SceneGraph* root) override;
    };
}

#endif //PAXENGINE3_TREESCENEGRAPHBUILDINGRULE_H
