//
// Created by Paul on 07.01.2018.
//

#include <opengl/resource/OpenGLSpriteSheet.h>

namespace PAX {
    namespace OpenGL {
        OpenGLSpriteSheet::OpenGLSpriteSheet(int textureCount) : SpriteSheet(textureCount), _oglTextures(textureCount, OpenGLTexture2D(-1)) {

        }

        OpenGLSpriteSheet::~OpenGLSpriteSheet() {

        }

        void OpenGLSpriteSheet::setOpenGLTextureAt(int i, OpenGLTexture2D texture) {
            _oglTextures[i] = texture;
            _textures[i] = &_oglTextures[i];
        }

        OpenGLTexture2D & OpenGLSpriteSheet::getOpenGLTextureAt(int i) {
            return _oglTextures[i];
        }
    }
}