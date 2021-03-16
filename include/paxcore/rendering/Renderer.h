//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_RENDERER_H
#define PAXENGINE3_RENDERER_H

#include <paxcore/world/scenegraph/WorldSceneGraph.h>
#include "scenegraph/generators/SceneGraphGenerator.h"
#include "scenegraph/nodes/SortingNode.h"
#include "RenderOptions.h"

namespace PAX {
    struct WorldSorter {
        static void sort(std::vector<WorldSceneGraph*> &worlds);
    };

    using WorldSortingNode = SortingNode<WorldSceneGraph, WorldSorter>;

    class Renderer {
        SceneGraph* sceneGraphRoot = nullptr;
        SceneGraph* generationEntryPoint = nullptr;
        WorldSortingNode sortingNode;

    public:
        EventHandler<RenderOptions&> OnTransformationChanged;

        void setSceneGraphRoot(SceneGraph *root);
        PAX_NODISCARD SceneGraph* getSceneGraphRoot() const;

        void setSceneGraphGenerationEntryPoint(SceneGraph *generationEntiryPoint);
        PAX_NODISCARD SceneGraph* getSceneGraphGenerationEntryPoint() const;

        virtual void initialize();
        virtual void render(RenderOptions & options);
    };
}

#endif //PAXENGINE3_RENDERER_H
