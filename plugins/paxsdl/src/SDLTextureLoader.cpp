//
// Created by Paul on 04.11.2017.
//

#include "paxsdl/SDLTextureLoader.h"

#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/resources/Resources.h>
#include <paxsdl/SDLTextureLoader.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/TextureFactory.h>
#include <paxcore/rendering/data/Image.h>


namespace PAX {
    SDLTextureLoader::SDLTextureLoader() = default;

    SDLTextureLoader::~SDLTextureLoader() = default;

    bool SDLTextureLoader::canLoad(Path path) const {
         return Services::GetResources().getLoader<Image>(path)->canLoad(path);
    }

    std::shared_ptr<Texture> SDLTextureLoader::load(Path path) {
        return Services::GetResources().loadOrGet<Image>(path)->toGPUTexture();
    }

    std::shared_ptr<Texture> SDLTextureLoader::loadOrGetFromJson(Resources &resources,
                                                                 const nlohmann::json & j) const {
        return resources.loadOrGet<Texture>(JsonToPath(j));
    }
}