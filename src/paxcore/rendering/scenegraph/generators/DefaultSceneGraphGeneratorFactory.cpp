//
// Created by Bittner on 10/07/2019.
//

#include <paxcore/rendering/scenegraph/generators/DefaultSceneGraphGeneratorFactory.h>
#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>

namespace PAX {
    SceneGraphGenerator * DefaultSceneGraphGeneratorFactory::create(int dimensions) {
        if (dimensions == 2)
            return new SortByZSceneGraphGenerator();
        else
            return new GroupByShadersSceneGraphGenerator();
    }
}