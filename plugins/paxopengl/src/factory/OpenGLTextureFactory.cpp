//
// Created by Bittner on 10/07/2019.
//

#include <paxopengl/factory/OpenGLTextureFactory.h>
#include <GL/glew.h>
#include <paxopengl/resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        std::shared_ptr<Texture> OpenGLTextureFactory::create(int width, int height) {
            GLuint id;
            glGenTextures(1, &id);
            return std::make_shared<OpenGLTexture2D>(id, width, height);
        }

        std::shared_ptr<Texture> OpenGLTextureFactory::create(int width, int height,
                                                              PAX::Texture::PixelFormat pixelFormat,
                                                              Texture::ColourType colourType) {
            GLuint id;
            glGenTextures(1, &id);
            std::shared_ptr<OpenGLTexture2D> t = std::make_shared<OpenGLTexture2D>(id, width, height);
            t->initEmptyTexture(pixelFormat, colourType);
            return t;
        }
    }
}