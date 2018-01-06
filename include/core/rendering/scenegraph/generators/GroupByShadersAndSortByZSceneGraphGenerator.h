//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
#define PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H

#include <core/rendering/scenegraph/SceneGraphGenerator.h>
#include <core/rendering/scenegraph/nodes/SortingNode.h>
#include "GroupByShadersSceneGraphGenerator.h"

namespace PAX {
    /**
     * This is the default SceneGraphGenerator for 2D scenes.
     * It sorts the the graphics objects in the scene by their z-coordinate. and groups shaders and sorts them
     * by their z position to fasten rendering. Therefore it will built the following structure:
     *
     *                    Root
     *                      |
     *         _____________|_______________
     *        |             |               |
     *   ShaderNode1   ShaderNode2 ... ShaderNodeN
     *        |             |               |
     *   SortingNode1  SortingNode2    SortingNodeN
     *        |             |               |
     *    Graphics      Graphics        Graphics
     */
    class GroupByShadersAndSortByZSceneGraphGenerator : public GroupByShadersSceneGraphGenerator {
    public:
        virtual void attach(ShadingNode &shadingNode, Graphics* g);
        virtual void detach(ShadingNode &shadingNode, Graphics* g);
    };
}

#endif //PAXENGINE3_SORTBYZANDGROUPBYSHADERSSCENEGRAPHGENERATOR_H
