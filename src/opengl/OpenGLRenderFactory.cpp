//
// Created by Paul on 02.07.2017.
//

#include <opengl/OpenGLRenderFactory.h>
#include <opengl/rendernodes/OpenGLWorldLayerRenderPass.h>
#include <core/world/WorldLayer.h>
#include <core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <core/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h>

namespace PAX {
    namespace OpenGL {
        WorldLayerSceneGraph* OpenGLRenderFactory::createSceneGraphNodeFor(WorldLayer *worldLayer, float z) {
            return new OpenGLWorldLayerRenderPass(z);
        }

        SceneGraphGenerator* OpenGLRenderFactory::createDefaultSceneGraphGenerator() {
            return new GroupByShadersAndSortByZSceneGraphGenerator();//new GroupByShadersSceneGraphGenerator();
        }
    }
}