//
// Created by Paul on 02.07.2017.
//

#include <GL/glew.h>
#include "../../../include/opengl/rendernodes/OpenGLWorldLayerRenderPass.h"

namespace PAX {
    namespace OpenGL {
        OpenGLWorldLayerRenderPass::OpenGLWorldLayerRenderPass() {}

        void OpenGLWorldLayerRenderPass::render(RenderOptions &renderOptions) {
            // Clear Depth buffer for each WorldLayer to not let them interfere. Each one should be unconditionally rendered on top of the previous
            glClear(GL_DEPTH_BUFFER_BIT);
            SceneGraph::render(renderOptions);
        }
    }
}