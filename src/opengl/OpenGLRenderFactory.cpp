//
// Created by Paul on 02.07.2017.
//

#include "../../include/opengl/OpenGLRenderFactory.h"
#include "../../include/opengl/rendernodes/OpenGLWorldLayerRenderPass.h"

namespace PAX {
    namespace OpenGL {
        SceneGraph* OpenGLRenderFactory::createWorldLayerSceneGraphNode() {
            return new OpenGLWorldLayerRenderPass();
        }
    }
}