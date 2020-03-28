//
// Created by Paul Bittner on 18.03.2020.
//

#include "paxsdl/SDLTextureLoader.h"
#include "paxopengl/resource/OpenGLTexture2D.h"

#ifdef PAX_WITH_SDLIMAGE
#include <SDL2/SDL_image.h>
#endif

#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/resources/Resources.h>
#include <paxsdl/SDLImageLoader.h>
#include <paxcore/service/Services.h>

namespace PAX {
    SDLImageLoader::SDLImageLoader() = default;

    SDLImageLoader::~SDLImageLoader() = default;

    bool SDLImageLoader::canLoad(Path path) const {
        Util::FileTypeChecker formats({
              "BMP", "GIF", "JPEG", "LBM", "PCX", "PNG", "PNM", "SVG", "TGA", "TIFF", "WEBP", "XCF", "XPM", "XV"
        });
        return formats.check(path.toString());
    }

    std::shared_ptr<Image> SDLImageLoader::load(Path path) {
#ifdef PAX_WITH_SDLIMAGE
        SDL_Surface* tex = nullptr;

        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            PAX_LOG(Log::Level::Error, "could not init SDL_Image: " << IMG_GetError());
        }

        if((tex = IMG_Load(path.c_str())) == nullptr) {
            PAX_THROW_RUNTIME_ERROR("Loading texture " << path << " failed.");
        }

        Texture::PixelFormat format = Texture::PixelFormat::RGB;
        if(tex->format->BytesPerPixel == 4) {
            format = Texture::PixelFormat::RGBA;
        }

        std::shared_ptr<Image> image = std::make_shared<Image>(tex->w, tex->h);
        image->setPixels(tex->pixels, format);
        SDL_FreeSurface(tex);

        return image;
#else
        assert(false);
        return nullptr;
#endif
    }

    std::shared_ptr<Image> SDLImageLoader::loadOrGetFromJson(Resources &resources,
                                                                 const nlohmann::json & j) const {
        return resources.loadOrGet<Image>(JsonToPath(j));
    }
}