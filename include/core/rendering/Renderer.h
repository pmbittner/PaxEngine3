//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_RENDERER_H
#define PAXENGINE3_RENDERER_H

#include "scenegraph/SceneGraphBuilder.h"

namespace PAX {
    class Renderer {
        SceneGraphBuilder _sceneGraphBuilder;

        SceneGraph* _sceneGraphRoot;
        SceneGraph* _generationEntryPoint;

    public:
        void setSceneGraphRoot(SceneGraph *root);
        SceneGraph* getSceneGraphRoot();

        void setSceneGraphGenerationEntryPoint(SceneGraph *generationEntiryPoint);
        SceneGraph* getSceneGraphGenerationEntryPoint();

        virtual void initialize();
        virtual void render();
    };
}

#endif //PAXENGINE3_RENDERER_H
