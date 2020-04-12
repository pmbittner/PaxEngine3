//
// Created by Paul on 30.06.2017.
//

#include <polypropylene/log/Log.h>
#include "paxopengl/resource/OpenGLTexture2D.h"

namespace PAX {
    namespace OpenGL {
        unsigned int OpenGLTexture2D::NumberOfActiveTextures = 0;

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
                    PAX_LOG(Log::Level::Warn, "Unknown WrapMode given! Was " << int(wrapMode));
                    return GL_REPEAT;
                }
            }
        }

        static GLint paxFilterModeToGLFilterMode(Texture::FilterMode filterMode) {
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

        static GLint paxPixelFormatToGLPixelFormat(Texture::PixelFormat pixelFormat) {
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

        static GLint paxColourTypeToColourType(Texture::ColourType c) {
            switch (c) {
                case Texture::ColourType::Float: {
                    return GL_FLOAT;
                }
                case Texture::ColourType::Byte: {
                    return GL_UNSIGNED_BYTE;
                }
                default: {
                    PAX_LOG(Log::Level::Warn, "Unknown ColourType given! Was " << int(c));
                    return GL_UNSIGNED_BYTE;
                }
            }
        }

        OpenGLTexture2D::OpenGLTexture2D(GLuint id, int width, int height) : id(id) {
            this->width = width;
            this->height = height;
        }

        OpenGLTexture2D::~OpenGLTexture2D() {
            // TODO: Schedule for cleanup instead of deleting directly.
            glDeleteTextures(1, &id);
        }

        void OpenGLTexture2D::setPixelFormat(PAX::Texture::PixelFormat format) {
            this->pixelFormat = format;
        }

        GLuint OpenGLTexture2D::getID() {
            return id;
        }

        void OpenGLTexture2D::setWrapMode(PAX::Texture::WrapMode horizontal, PAX::Texture::WrapMode vertical) {
            Texture::setWrapMode(horizontal, vertical);

            // FIXME: Binding here is bad, if there is currently another texture bound.
            bind();
            ensureWrappingMode();
            unbind();
        }

        void OpenGLTexture2D::setFilterMode(PAX::Texture::FilterMode mode) {
            Texture::setFilterMode(mode);

            // FIXME: Binding here is bad, if there is currently another texture bound.
            bind();
            ensureFilterMode();
            unbind();
        }

        void OpenGLTexture2D::setPixels(void *data, PAX::Texture::PixelFormat dataPixelFormat, ColourType colourType) {
            setPixelFormat(dataPixelFormat);
            this->colourType = colourType;

            // FIXME: Binding here is bad, if there is currently another texture bound.
            bind();
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            GLenum glPixelFormat = paxPixelFormatToGLPixelFormat(dataPixelFormat);
            GLenum glColourType = paxColourTypeToColourType(colourType);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    glPixelFormat,
                    getWidth(),
                    getHeight(),
                    0,
                    glPixelFormat,
                    glColourType,
                    data);
            unbind();
        }

        void OpenGLTexture2D::initEmptyTexture(PAX::Texture::PixelFormat dataPixelFormat,
                                               PAX::Texture::ColourType colourType) {
            setPixels(nullptr, dataPixelFormat, colourType);
            bind();
            ensureWrappingMode();
            ensureFilterMode();
            unbind();
        }

        void OpenGLTexture2D::bind() {
            glActiveTexture(GL_TEXTURE0 + NumberOfActiveTextures);
            glBindTexture(GL_TEXTURE_2D, id);
            //std::cout << "[OpenGLTexture2D::bind] " << _id << " to unit " << NumberOfActiveTextures << std::endl;
            ++NumberOfActiveTextures;
        }

        void OpenGLTexture2D::unbind() {
            --NumberOfActiveTextures;
            //std::cout << "[OpenGLTexture2D::unbind] " << _id << " from unit " << NumberOfActiveTextures << std::endl;
            glActiveTexture(GL_TEXTURE0 + NumberOfActiveTextures);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void OpenGLTexture2D::ensureFilterMode() {
            FilterMode mode = getFilterMode();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paxFilterModeToGLFilterMode(mode));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paxFilterModeToGLFilterMode(mode));
        }

        void OpenGLTexture2D::ensureWrappingMode() {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paxWrapModeToGLWrapMode(getWrapModeHorizontal()));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paxWrapModeToGLWrapMode(getWrapModeVertical()));
        }
    }
}