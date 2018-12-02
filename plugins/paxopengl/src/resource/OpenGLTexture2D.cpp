//
// Created by Paul on 30.06.2017.
//

#include <easylogging++.h>
#include <resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        static GLint paxWrapModeToGLWrapMode(Texture::WrapMode wrapMode) {
            switch (wrapMode) {
                case Texture::WrapMode::Repeat: {
                    return GL_REPEAT;
                }
                case Texture::WrapMode::MirrorRepeat: {
                    return GL_MIRRORED_REPEAT;
                }
                case Texture::WrapMode::ClampToEdge: {
                    return GL_CLAMP_TO_EDGE;
                }
                case Texture::WrapMode::ClampToBorder: {
                    return GL_CLAMP_TO_BORDER;
                }
                default: {
                    return GL_REPEAT;
                }
            }
        }

        OpenGLTexture2D::OpenGLTexture2D(GLuint id, int width, int height) : _id(id) {
            _width = width;
            _height = height;
        }

        OpenGLTexture2D::~OpenGLTexture2D() {

        }

        GLuint OpenGLTexture2D::getID() {
            return _id;
        }

        void OpenGLTexture2D::setWrapMode(PAX::Texture::WrapMode horizontal, PAX::Texture::WrapMode vertical) {
            Texture::setWrapMode(horizontal, vertical);

            // FIXME: Binding here is bad, if there is currently another texture bound. As this is an undesired case
            // we do not unbind to see this texture for debugging purposes, but I don't know if this is really a good idea.
            bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paxWrapModeToGLWrapMode(horizontal));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paxWrapModeToGLWrapMode(vertical));
        }

        void OpenGLTexture2D::bind() {
            glBindTexture(GL_TEXTURE_2D, _id);
        }

        void OpenGLTexture2D::unbind() {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}