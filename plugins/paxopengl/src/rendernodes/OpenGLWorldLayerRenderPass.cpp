//
// Created by Paul on 02.07.2017.
//

#include <GL/glew.h>
#include <rendernodes/OpenGLWorldLayerRenderPass.h>
#include <paxcore/world/WorldLayer.h>

namespace PAX {
    namespace OpenGL {
        OpenGLWorldLayerRenderPass::OpenGLWorldLayerRenderPass(float z) : WorldLayerSceneGraph(z) {

        }

        void OpenGLWorldLayerRenderPass::render(RenderOptions &renderOptions) {
            // Clear Depth buffer for each WorldLayer to not let them interfere. Each one should be unconditionally rendered on top of the previous.
            glClear(GL_DEPTH_BUFFER_BIT);

            bool is2D = this->getWorldLayer()->getDimensions() == 2;
            if (is2D)
                glDisable(GL_DEPTH_TEST);

            WorldLayerSceneGraph::render(renderOptions);

            if (is2D)
                glEnable(GL_DEPTH_TEST);
        }
    }
}