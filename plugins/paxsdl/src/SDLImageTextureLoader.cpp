//
// Created by Paul on 04.11.2017.
//

#include "paxsdl/SDLImageTextureLoader.h"
#include "paxopengl/resource/OpenGLTexture2D.h"

#ifdef PAX_WITH_SDLIMAGE
#include <SDL2/SDL_image.h>
#endif

#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/resources/Resources.h>
#include <assert.h>
#include <paxsdl/SDLImageTextureLoader.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/TextureFactory.h>


namespace PAX {
    SDLImageTextureLoader::SDLImageTextureLoader() = default;

    SDLImageTextureLoader::~SDLImageTextureLoader() = default;

    bool SDLImageTextureLoader::canLoad(Path path) const {
        Util::FileTypeChecker formats({
                "BMP", "GIF", "JPEG", "LBM", "PCX", "PNG", "PNM", "SVG", "TGA", "TIFF", "WEBP", "XCF", "XPM", "XV"
        });

        return formats.check(path.toString());
    }

    std::shared_ptr<Texture> SDLImageTextureLoader::load(Path path) {
#ifdef PAX_WITH_SDLIMAGE
        SDL_Surface* tex = nullptr;

        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            PAX_LOG(Log::Level::Error, "could not init SDL_Image: " << IMG_GetError());
        }

        if((tex = IMG_Load(path.c_str())) == nullptr) {
            PAX_LOG(Log::Level::Error, "Loading texture " << path << " failed.");
        }

        Texture::PixelFormat format = Texture::PixelFormat::RGB;
        if(tex->format->BytesPerPixel == 4) {
            format = Texture::PixelFormat::RGBA;
        }

        std::shared_ptr<Texture> texture = Services::GetFactoryService().get<TextureFactory>()->create(tex->w, tex->h);
        texture->setPixels(tex->pixels, format);
        texture->setFilterMode(Texture::FilterMode::Nearest);

        SDL_FreeSurface(tex);

        return texture;
#else
        assert(false);
        return nullptr;
#endif
    }

    std::shared_ptr<Texture> SDLImageTextureLoader::loadOrGetFromJson(Resources &resources,
            const nlohmann::json & j) const {
        return resources.loadOrGet<Texture>(JsonToPath(j));
    }
}