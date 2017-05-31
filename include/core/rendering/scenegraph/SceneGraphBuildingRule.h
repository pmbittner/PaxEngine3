//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHAGENT_H
#define PAXENGINE3_SCENEGRAPHAGENT_H

namespace PAX {
    class Graphics;
    class SceneGraph;

    class SceneGraphBuildingRule {
    public:
        virtual SceneGraph* determineSceneGraphNodeFor(Graphics *graphics, SceneGraph* root) = 0;
    };
}

#endif //PAXENGINE3_SCENEGRAPHAGENT_H
