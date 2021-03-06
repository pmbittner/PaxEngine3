//
// Created by Paul Bittner on 06.03.2021.
//

#include "paxopengl/Conversion.h"

namespace PAX::OpenGL {
    GLint ToOpenGL(Texture::PixelFormat pixelFormat) {
        switch (pixelFormat) {
            case Texture::PixelFormat::RGB: {
                return GL_RGB;
            }
            case Texture::PixelFormat::RGBA: {
                return GL_RGBA;
            }
            case Texture::PixelFormat::BGR: {
                return GL_BGR;
            }
            default: {
                PAX_LOG(Log::Level::Warn, "Unknown PixelFormat given! Was " << int(pixelFormat));
                return GL_RGB;
            }
        }
    }

    GLint ToOpenGL(Texture::WrapMode wrapMode) {
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
                PAX_LOG(Log::Level::Warn, "Unknown WrapMode given! Was " << int(wrapMode));
                return GL_REPEAT;
            }
        }
    }

    GLint ToOpenGL(Texture::FilterMode filterMode) {
        switch (filterMode) {
            case Texture::FilterMode::Nearest: {
                return GL_NEAREST;
            }
            case Texture::FilterMode::Linear: {
                return GL_LINEAR;
            }
            default: {
                PAX_LOG(Log::Level::Warn, "Unknown FilterMode given! Was " << int(filterMode));
                return GL_NEAREST;
            }
        }
    }
}