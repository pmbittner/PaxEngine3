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
        pixels = new Colour[width * height];
        std::memset(pixels, 0, width*height*sizeof(Colour));
    }

    void Image::setColorAt(const glm::ivec2 &pixel, const Colour &colour) {
        pixels[pixel.x + pixel.y * width] = colour;
    }

    void Image::fill(const PAX::Colour &colour) {
        std::fill(pixels, pixels + (width * height) - 1, colour);
    }

    void Image::drawLine(const glm::vec2 &from, const glm::vec2 &to, const Colour &color) {
        glm::vec2 p = from;
        glm::vec2 q = to;

        const bool steep = (fabs(q.y - p.y) > fabs(q.x - p.x));
        if(steep)
        {
            std::swap(p.x, p.y);
            std::swap(q.x, q.y);
        }

        if(p.x > q.x)
        {
            std::swap(p.x, q.x);
            std::swap(p.y, q.y);
        }

        const float dx = q.x - p.x;
        const float dy = fabs(q.y - p.y);

        float error = dx / 2.0f;
        const int ystep = (p.y < q.y) ? 1 : -1;
        int y = (int)p.y;

        const int maxX = (int)q.x;

        for(int x=(int)p.x; x<=maxX; x++)
        {
            if(steep)
            {
                setColorAt({y, x}, color);
            }
            else
            {
                setColorAt({x, y}, color);
            }

            error -= dy;
            if(error < 0)
            {
                y += ystep;
                error += dx;
            }
        }
    }

    void Image::fillRect(const glm::vec2 &p, const glm::vec2 & q, const Colour & colour) {
        int startX = std::min(p.x, q.x);
        int startY = std::min(p.y, q.y);
        int toX = std::max(p.x, q.x);
        int toY = std::max(p.y, q.y);

        for (int y = startY; y <= toY; ++y) {
            Colour * first = pixels + width*y + startX;
            Colour * last  = pixels + width*y + toX + 1;
            std::fill(first, last, colour);
        }
    }

    void Image::bind() {}
    void Image::unbind() {}

    void Image::setPixels(void *data, PixelFormat dataPixelFormat) {
        size_t numPixels = width * height;

        if (dataPixelFormat != PixelFormat::RGBA) {
            char * others = static_cast<char *>(data);

            if (dataPixelFormat == PixelFormat::RGB) {
                for (size_t i = 0; i < numPixels; ++i) {
                    size_t dataIndex = i * 3;
                    pixels[i].r = others[dataIndex];
                    pixels[i].g = others[dataIndex + 1];
                    pixels[i].b = others[dataIndex + 2];
                    pixels[i].a = char(255);
                }
            } else if (dataPixelFormat == PixelFormat::BGR) {
                for (size_t i = 0; i < numPixels; ++i) {
                    size_t dataIndex = i * sizeof(Colour);
                    pixels[i].b = others[dataIndex];
                    pixels[i].g = others[dataIndex + 1];
                    pixels[i].r = others[dataIndex + 2];
                    pixels[i].a = char(255);
                }
            }
        } else {
            memcpy(pixels, data, numPixels * sizeof(Colour));
        }
    }

    const Colour * Image::getPixels() const {
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