//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHGENERATABLE_H
#define PAXENGINE3_SCENEGRAPHGENERATABLE_H

namespace PAX {
    class SceneGraph;
    class SceneGraphBuildingRule;

    class SceneGraphGeneratable {
        SceneGraph *_mySceneGraphNode;
    public:
        SceneGraph* getSceneGraphNode();
        void setSceneGraphNode(SceneGraph *sceneGraph);
        virtual SceneGraphBuildingRule* getSceneGraphBuildingRule() = 0;
    };
}

#endif //PAXENGINE3_SCENEGRAPHGENERATABLE_H
