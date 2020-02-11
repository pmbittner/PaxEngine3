//
// Created by bittner on 11/20/17.
//

#include <vector>
#include <paxutil/math/Conversion.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/TextureFactory.h>
#include <paxcore/rendering/loader/NullTextureLoader.h>

namespace PAX {
    NullTextureLoader::NullTextureLoader() = default;

    NullTextureLoader::~NullTextureLoader() = default;

    bool NullTextureLoader::canLoad(Path path) const {
        return true;
    }

    std::shared_ptr<PAX::Texture> NullTextureLoader::load(Path path) {
        if (!_texture) {
            int w = 16;
            int h = w;

            const Texture::PixelFormat pixelFormat = Texture::PixelFormat::RGB;
            int pixelCount = w * h;
            std::vector<char> pixels(pixelCount * 3);

            struct Pixel {
                int x;
                int y;
            };
            int xoffset = 6;//2 for 8x8 pixels
            int yoffset = 5;//1 for 8x8 pixels
            std::vector<Pixel> errorLetter = {
                    {0, 0},
                    {1, 0},
                    {2, 0},
                    {3, 0},
                    {0, 1},
                    {0, 2},
                    {1, 2},
                    {2, 2},
                    {0, 3},
                    {0, 4},
                    {0, 5},
                    {1, 5},
                    {2, 5},
                    {3, 5},
            };

            /*
            for (int i = 0; i < pixelCount; ++i) {
                int index = 3*i;
                pixels[index] = pixels[index+1] = pixels[index+2] = 0;
            }
            //*/

            for (Pixel &p: errorLetter) {
                int index = 3 * PAX::Util::Conversion::coordinatesToIndex(w, p.x + xoffset, p.y + yoffset);
                pixels[index] = char(255);
                pixels[index + 1] = char(255);
                pixels[index + 2] = char(255);
            }

            _texture = Services::GetFactoryService().get<TextureFactory>()->create(w, h);
            _texture->setPixels(&pixels.front(), pixelFormat);
            _texture->setFilterMode(Texture::FilterMode::Nearest);
        }

        return _texture;
    }

    std::shared_ptr<Texture> NullTextureLoader::loadOrGetFromJson(PAX::Resources &resources,
                                                                               const nlohmann::json & j) const {
        return resources.loadOrGet<Texture>(JsonToPath(j));
    }
}