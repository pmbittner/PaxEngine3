//
// Created by Paul on 30.06.2017.
//

#include <easylogging++.h>
#include <resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        OpenGLTexture2D::OpenGLTexture2D(GLuint id, int width, int height) : _id(id) {
            _width = width;
            _height = height;
        }

        OpenGLTexture2D::~OpenGLTexture2D() {

        }

        GLuint OpenGLTexture2D::getID() {
            return _id;
        }

        void OpenGLTexture2D::bind() {
            glBindTexture(GL_TEXTURE_2D, _id);
        }

        void OpenGLTexture2D::unbind() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}