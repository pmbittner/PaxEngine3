//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
#define PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H

#include <paxcore/rendering/scenegraph/SceneGraphGenerator.h>
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
            virtual void render(RenderOptions &renderOptions) override;
        } sortingNode;

    public:
        SortByZSceneGraphGenerator();
        virtual ~SortByZSceneGraphGenerator();

        virtual void addGraphics(const std::shared_ptr<Graphics> & g) override;
        virtual void removeGraphics(const std::shared_ptr<Graphics> & g) override;
    };
}

#endif //PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
