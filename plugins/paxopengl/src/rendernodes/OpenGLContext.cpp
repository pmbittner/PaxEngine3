//
// Created by Paul on 17.06.2017.
//

#include <GL/glew.h>
#include <paxcore/Engine.h>

#include "paxopengl/OpenGLError.h"
#include "paxopengl/rendernodes/OpenGLContext.h"

namespace PAX {
    namespace OpenGL {
        OpenGLContext::OpenGLContext() = default;

        void OpenGLContext::initialize() {
            const std::shared_ptr<Window> window = Services::GetWindowService().getWindow();
            glm::ivec2 res = window->getResolution();

#ifdef PAX_BUILD_TYPE_DEBUG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(GLErrorCallback, nullptr);
#endif

            //glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_MULTISAMPLE);
            //glEnable(GL_BACK);

            //glEnable(GL_CULL_FACE);

            // ----- enable alpha blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//            glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
            //glMatrixMode(GL_PROJECTION);

            // TODO: Make this configurable
            glClearColor(0.8, 0.8, 0.8, 1);

            PAX_GLERROR("OpenGLContext::initialize");
        }

        void OpenGLContext::render(RenderOptions &renderOptions) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SceneGraph::render(renderOptions);
        }
    }
}