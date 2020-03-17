//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_RENDERER_H
#define PAXENGINE3_RENDERER_H

#include "paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h"
#include "RenderOptions.h"

namespace PAX {
    class Renderer {
        SceneGraph* sceneGraphRoot = nullptr;
        SceneGraph* generationEntryPoint = nullptr;

    public:
        EventHandler<RenderOptions&> OnTransformationChanged;

        void setSceneGraphRoot(SceneGraph *root);
        SceneGraph* getSceneGraphRoot();

        void setSceneGraphGenerationEntryPoint(SceneGraph *generationEntiryPoint);
        SceneGraph* getSceneGraphGenerationEntryPoint();

        virtual void initialize();
        virtual void render(RenderOptions & options);
    };
}

#endif //PAXENGINE3_RENDERER_H
