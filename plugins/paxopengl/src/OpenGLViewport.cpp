//
// Created by Paul on 29.06.2017.
//

#include <iostream>

#include <GL/glew.h>

#include "paxopengl/OpenGLViewport.h"

namespace PAX {
    namespace OpenGL {
        OpenGLViewport::OpenGLViewport() : Viewport() {}

        OpenGLViewport::OpenGLViewport(int x, int y, int w, int h, ResizePolicy resizePolicy) : Viewport(x, y, w, h, resizePolicy) {}

        void OpenGLViewport::apply() {
            glViewport(_x, _y, _w, _h);
        }
    }
}