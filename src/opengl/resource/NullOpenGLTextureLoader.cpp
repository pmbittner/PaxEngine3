//
// Created by bittner on 11/20/17.
//

#include <opengl/resource/OpenGLNullTextureLoader.h>
#include <opengl/resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        OpenGLNullTextureLoader::OpenGLNullTextureLoader() {

        }

        OpenGLNullTextureLoader::~OpenGLNullTextureLoader() {

        }

        bool OpenGLNullTextureLoader::canLoad(const char *path) {
            return true;
        }

        PAX::Texture *OpenGLNullTextureLoader::load(const char *path) {
            int w = 16;
            int h = w;

            int mode = GL_RGB;
            char pixels[w * h * 3];

            GLuint id;
            glGenTextures(1, &id);

            OpenGLTexture2D *ogltexture = new OpenGLTexture2D(id, w, h);

            ogltexture->bind();

            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
            glTexImage2D(GL_TEXTURE_2D, 0, mode, ogltexture->getWidth(), ogltexture->getHeight(), 0, mode, GL_UNSIGNED_BYTE, &pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            ogltexture->unbind();

            return ogltexture;
        }

        bool OpenGLNullTextureLoader::free(Texture *res) {
            delete res;
        }
    }
}