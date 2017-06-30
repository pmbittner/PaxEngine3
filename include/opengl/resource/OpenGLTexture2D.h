//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURE2D_H
#define PAXENGINE3_OPENGLTEXTURE2D_H

#include <GL/glew.h>
#include <string>

#include "../../core/rendering/resource/Texture.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLTexture2D : public Texture {
            GLuint _id;
            int _w, _h;

        public:
            OpenGLTexture2D(std::string path);
            ~OpenGLTexture2D();

            virtual void bind() override;
            virtual void unbind() override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURE2D_H
