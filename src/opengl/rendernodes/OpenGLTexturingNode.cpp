//
// Created by Paul on 07.12.2017.
//

#include <opengl/rendernodes/OpenGLTexturingNode.h>

namespace PAX {
    namespace OpenGL {
        OpenGLTexturingNode::OpenGLTexturingNode(Texture *texture) : TexturingNode(texture) {

        }

        void OpenGLTexturingNode::render(RenderOptions &renderOptions) {
            glActiveTexture(GL_TEXTURE0);
            //renderOptions.getShaderOptions().getShader()->setUniform("textureSampler", 0);
            TexturingNode::render(renderOptions);
        }
    }
}