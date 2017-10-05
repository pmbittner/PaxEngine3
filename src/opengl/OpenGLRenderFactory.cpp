//
// Created by Paul on 02.07.2017.
//

#include <opengl/OpenGLRenderFactory.h>
#include <opengl/rendernodes/OpenGLWorldLayerRenderPass.h>
#include <core/world/WorldLayer.h>
#include <core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>

namespace PAX {
    namespace OpenGL {
        SceneGraph* OpenGLRenderFactory::createSceneGraphNodeFor(WorldLayer *worldLayer) {
            return new OpenGLWorldLayerRenderPass();
        }

        SceneGraphGenerator* OpenGLRenderFactory::createSceneGraphGeneratorFor(WorldLayer *worldLayer) {
            return new GroupByShadersSceneGraphGenerator();
        }
    }
}