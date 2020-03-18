//
// Created by Paul Bittner on 18.03.2020.
//

#ifndef PAXENGINE3_SDLIMAGELOADER_H
#define PAXENGINE3_SDLIMAGELOADER_H

#include <paxcore/rendering/data/Image.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    class SDLImageLoader : public ResourceLoader<Image, Path> {
    public:
        SDLImageLoader();
        ~SDLImageLoader() override;

        PAX_NODISCARD bool canLoad(Path path) const override;
        PAX_NODISCARD std::shared_ptr<Image> load(Path path) override;
        PAX_NODISCARD std::shared_ptr<Image> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
    };
}

#endif //PAXENGINE3_SDLIMAGELOADER_H
