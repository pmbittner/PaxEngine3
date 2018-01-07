//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_OPENGLSPRITESHEET_H
#define PAXENGINE3_OPENGLSPRITESHEET_H

#include <core/rendering/resource/SpriteSheet.h>
#include "OpenGLTexture2D.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLSpriteSheet : public SpriteSheet {
            std::vector<OpenGLTexture2D> _oglTextures;

        public:
            OpenGLSpriteSheet(int textureCount);
            ~OpenGLSpriteSheet();

            void setOpenGLTextureAt(int i, OpenGLTexture2D texture);
            OpenGLTexture2D& getOpenGLTextureAt(int i);
        };
    }
}

#endif //PAXENGINE3_OPENGLSPRITESHEET_H
