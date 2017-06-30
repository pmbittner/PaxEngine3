//
// Created by Paul on 29.06.2017.
//
#include <GL/glew.h>
#include <iostream>
#include "../../include/opengl/OpenGLViewport.h"

namespace PAX {
    namespace OpenGL {
        OpenGLViewport::OpenGLViewport() : Viewport() {}

        OpenGLViewport::OpenGLViewport(int x, int y, int w, int h) : Viewport(x, y, w, h) {}

        void OpenGLViewport::apply() {
            glViewport(_x, _y, _w, _h);
        }
    }
}