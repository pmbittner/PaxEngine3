//
// Created by Paul on 17.06.2017.
//

#include <GL/glew.h>
#include "../../include/opengl/OpenGLRenderPass.h"
#include "../../include/core/Engine.h"

namespace PAX {
    OpenGLRenderPass::OpenGLRenderPass() {

    }

    void OpenGLRenderPass::initialize() {
        LOG(INFO) << "Initializing OpenGL";

        Window *window = Engine::GetInstance()->getWindow();
        glm::vec2 res = window->getResolution();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BACK);

        // ----- enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glMatrixMode(GL_PROJECTION);

        glClearColor(0.5f, 0, 0.5f, 1);
        glViewport(0, 0, res.x, res.y);
    }

    void OpenGLRenderPass::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SceneGraph::render();
    }
}