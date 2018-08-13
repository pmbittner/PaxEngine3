//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURE2D_H
#define PAXENGINE3_OPENGLTEXTURE2D_H

#include <GL/glew.h>
#include <string>

#include <core/rendering/resource/Texture.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLTexture2D : public Texture {
            GLuint _id;

        public:
            OpenGLTexture2D(GLuint id, int width = -1, int height = -1);
            ~OpenGLTexture2D();

            GLuint getID();

            virtual void bind() override;
            virtual void unbind() override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURE2D_H
