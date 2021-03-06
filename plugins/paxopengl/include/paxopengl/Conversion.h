//
// Created by Paul Bittner on 06.03.2021.
//

#ifndef MESHFOLD_CONVERSION_H
#define MESHFOLD_CONVERSION_H

#include <GL/glew.h>
#include "paxcore/rendering/data/Texture.h"

namespace PAX::OpenGL {
    GLint ToOpenGL(Texture::PixelFormat pixelFormat);
    GLint ToOpenGL(Texture::WrapMode wrapMode);
    GLint ToOpenGL(Texture::FilterMode filterMode);
}

#endif //MESHFOLD_CONVERSION_H
