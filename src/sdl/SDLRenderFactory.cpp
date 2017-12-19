//
// Created by Paul on 02.07.2017.
//

#include <sdl/SDLRenderFactory.h>
#include <core/rendering/scenegraph/SceneGraph.h>
#include <core/world/WorldLayer.h>
#include <core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>

namespace PAX {
    namespace SDL {
        SceneGraph * SDLRenderFactory::createSceneGraphNodeFor(WorldLayer *worldLayer) {
            return new SceneGraph();
        }

        SceneGraphGenerator * SDLRenderFactory::createDefaultSceneGraphGenerator() {
            return new GroupByShadersSceneGraphGenerator();
        }
    }
}