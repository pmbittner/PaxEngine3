//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURE2D_H
#define PAXENGINE3_OPENGLTEXTURE2D_H

#include <GL/glew.h>
#include <string>

#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLTexture2D : public Texture {
            GLuint id;

            // We count the number of active textures here.
            // This is some sort of hacky, but we expect only one OpenGLContext to occur.
            static unsigned int NumberOfActiveTextures;

        public:
            explicit OpenGLTexture2D(GLuint id, int width = -1, int height = -1);
            ~OpenGLTexture2D() override;

            GLuint getID();

            void setWrapMode(WrapMode horizontal, WrapMode vertical) override;
            void setFilterMode(FilterMode mode) override;

            void setPixels(void * data, PixelFormat dataPixelFormat) override;

            void bind() override;
            void unbind() override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURE2D_H
