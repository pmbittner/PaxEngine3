//
// Created by Paul on 30.06.2017.
//

#include <SDL.h>

#ifdef PAX_WITH_SDLIMAGE
#include <SDL_image.h>
#endif

#include "../../../include/opengl/resource/OpenGLTexture2D.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    namespace OpenGL {
        OpenGLTexture2D::OpenGLTexture2D(GLuint id, int width, int height) : _id(id) {
            _width = width;
            _height = height;
        }

        OpenGLTexture2D::~OpenGLTexture2D() {
            glDeleteTextures(1, &_id);
        }

        void OpenGLTexture2D::bind() {
            glBindTexture(GL_TEXTURE_2D, _id);
        }

        void OpenGLTexture2D::unbind() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}