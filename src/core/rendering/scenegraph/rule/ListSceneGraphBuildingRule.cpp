//
// Created by Paul on 26.05.2017.
//

#include "../../../../../include/core/rendering/scenegraph/rule/ListSceneGraphBuildingRule.h"

namespace PAX {
    SceneGraph * ListSceneGraphBuildingRule::determineSceneGraphNodeFor(EntityComponent *component, SceneGraph *root) {
        return root;
    }
}