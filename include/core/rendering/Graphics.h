//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include "Renderable.h"
#include "../entity/EntityComponent.h"
#include "scenegraph/SceneGraphBuildingRule.h"

namespace PAX {
    PAX_EntityComponent(Graphics, false, public Renderable)
        // The SceneGraph that holds this Graphics for rendering
        SceneGraph* _sceneGraph = nullptr;

    public:
        SceneGraph* getSceneGraph();
        void setSceneGraph(SceneGraph *sceneGraph);

        virtual SceneGraphBuildingRule* getSceneGraphBuildingRule() = 0;
        virtual float getZ() override;
    };
}

#endif //PAXENGINE3_GRAPHICS_H
