//
// Created by Paul Bittner on 18.03.2020.
//

#include <paxcore/rendering/data/Image.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/TextureFactory.h>

namespace PAX {
    Image::Image(int width, int height) : Texture() {
        this->width = width;
        this->height = height;
        reallocatePixelBuffer();
    }

    Image::~Image() {
        delete pixels;
    }

    void Image::reallocatePixelBuffer() {
        delete pixels;
        pixels = new glm::cvec4[sizeof(glm::cvec4) * width * height];
    }

    void Image::bind() {}
    void Image::unbind() {}

    void Image::setPixels(void *data, PixelFormat dataPixelFormat) {
        size_t numPixels = width * height;

        if (dataPixelFormat != PixelFormat::RGBA) {
            char * others = static_cast<char *>(data);

            if (dataPixelFormat == PixelFormat::RGB) {
                for (size_t i = 0; i < numPixels; ++i) {
                    size_t dataIndex = i * sizeof(glm::cvec4);
                    pixels[i].r = others[dataIndex];
                    pixels[i].g = others[dataIndex + 1];
                    pixels[i].b = others[dataIndex + 2];
                    pixels[i].a = char(255);
                }
            } else if (dataPixelFormat == PixelFormat::BGR) {
                for (size_t i = 0; i < numPixels; ++i) {
                    size_t dataIndex = i * sizeof(glm::cvec4);
                    pixels[i].b = others[dataIndex];
                    pixels[i].g = others[dataIndex + 1];
                    pixels[i].r = others[dataIndex + 2];
                    pixels[i].a = char(255);
                }
            }
        } else {
            memcpy(pixels, data, numPixels * sizeof(glm::cvec4));
        }
    }

    const glm::cvec4* Image::getPixels() const {
        return pixels;
    }

    std::shared_ptr<Texture> Image::toGPUTexture() const {
        std::shared_ptr<Texture> tex = Services::GetFactoryService().get<TextureFactory>()->create(width, height);
        tex->bind();
        tex->setFilterMode(getFilterMode());
        tex->setWrapMode(getWrapModeHorizontal(), getWrapModeVertical());
        tex->setPixels(pixels, PixelFormat::RGBA);
        tex->unbind();
        return tex;
    }
}