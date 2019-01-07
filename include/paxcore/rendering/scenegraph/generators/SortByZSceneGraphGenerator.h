//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
#define PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H

#include <paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/nodes/SortingNode.h>
#include "GroupByShadersSceneGraphGenerator.h"

namespace PAX {
    /**
     * This is the default SceneGraphGenerator for 2D scenes.
     * It sorts the the graphics objects in the scene by their z-coordinate.
     *
     *                    Root
     *                      |
     *                 SortingNode
     *         _____________|_______________
     *        |             |               |
     *   ShaderNode1   ShaderNode2 ... ShaderNodeN
     *        |             |               |
     *    Graphics      Graphics        Graphics
     */
    class SortByZSceneGraphGenerator : public SceneGraphGenerator {
        class SortingNode : public TypedSceneGraph<Graphics> {
            Sort::BackToFrontGraphicsSort sorter;

        public:
            SortingNode();
            void render(RenderOptions &renderOptions) override;
        } sortingNode;

    protected:
        void addGraphics(Graphics * g) override;
        void removeGraphics(Graphics * g) override;

    public:
        SortByZSceneGraphGenerator();
        ~SortByZSceneGraphGenerator() override;
    };
}

#endif //PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
