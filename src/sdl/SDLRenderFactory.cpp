//
// Created by Paul on 02.07.2017.
//

#include <sdl/SDLRenderFactory.h>
#include <core/rendering/scenegraph/SceneGraph.h>
#include <core/world/WorldLayer.h>
#include <core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>

namespace PAX {
    namespace SDL {
        WorldLayerSceneGraph * SDLRenderFactory::createSceneGraphNodeFor(WorldLayer *worldLayer, float z) {
            return new WorldLayerSceneGraph(z);
        }

        SceneGraphGenerator * SDLRenderFactory::createDefaultSceneGraphGenerator() {
            return new GroupByShadersSceneGraphGenerator();
        }
    }
}