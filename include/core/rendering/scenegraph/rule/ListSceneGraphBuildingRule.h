//
// Created by Paul on 26.05.2017.
//

#ifndef PAXENGINE3_LISTSCENEGRAPHBUILDINGRULE_H
#define PAXENGINE3_LISTSCENEGRAPHBUILDINGRULE_H

#include "../SceneGraphBuildingRule.h"

namespace PAX {
    class ListSceneGraphBuildingRule : public SceneGraphBuildingRule {
    public:
        virtual SceneGraph* determineSceneGraphNodeFor(Graphics *graphics, SceneGraph* root) override;
    };
}

#endif //PAXENGINE3_LISTSCENEGRAPHBUILDINGRULE_H
