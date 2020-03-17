//
// Created by Paul on 02.07.2017.
//

#include <GL/glew.h>

#include "paxopengl/rendernodes/OpenGLDefaultWorldSceneGraph.h"
#include "paxcore/world/World.h"

namespace PAX {
    namespace OpenGL {
        OpenGLDefaultWorldSceneGraph::OpenGLDefaultWorldSceneGraph() : WorldSceneGraph() {}

        void OpenGLDefaultWorldSceneGraph::render(RenderOptions &renderOptions) {
            // Clear Depth buffer for each WorldLayer to not let them interfere. Each one should be unconditionally rendered on top of the previous.
            glClear(GL_DEPTH_BUFFER_BIT);

            const bool is2D = this->getWorld()->getDimensions() == 2;
            if (is2D)
                glDisable(GL_DEPTH_TEST);

            WorldSceneGraph::render(renderOptions);

            if (is2D)
                glEnable(GL_DEPTH_TEST);
        }
    }
}