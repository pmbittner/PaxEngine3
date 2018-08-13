//
// Created by Paul on 17.06.2017.
//

#include <GL/glew.h>
#include <utility/Error.h>
#include <rendernodes/OpenGLRenderPass.h>
#include <core/Engine.h>

namespace PAX {
    namespace OpenGL {
        OpenGLRenderPass::OpenGLRenderPass() {

        }

        void OpenGLRenderPass::initialize() {
            LOG(INFO) << "OPENGL INITIALIZATION";

            Window *window = Engine::Instance().getWindow();
            glm::vec2 res = window->getResolution();

            glEnable(GL_TEXTURE_2D);
            //glEnable(GL_DEPTH_TEST);
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_BACK);

            // ----- enable alpha blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glMatrixMode(GL_PROJECTION);

            glClearColor(0.8, 0.8, 0.8, 1);
            glViewport(0, 0, res.x, res.y);

            catchError("OpenGLRenderPass::initialize", false);
            LOG(INFO) << "OPENGL INITIALIZATION DONE";
        }

        void OpenGLRenderPass::render(RenderOptions &renderOptions) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SceneGraph::render(renderOptions);
        }
    }
}