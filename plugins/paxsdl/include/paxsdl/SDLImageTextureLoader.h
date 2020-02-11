//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_SDLIMAGETEXTURELOADER_H
#define PAXENGINE3_SDLIMAGETEXTURELOADER_H

#include <paxcore/rendering/data/Texture.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    class SDLImageTextureLoader : public ResourceLoader<Texture, Path> {
    public:
        SDLImageTextureLoader();
        ~SDLImageTextureLoader() override;

        PAX_NODISCARD bool canLoad(Path path) const override;
        PAX_NODISCARD std::shared_ptr<Texture> load(Path path) override;
        PAX_NODISCARD std::shared_ptr<Texture> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
    };
}

#endif //PAXENGINE3_SDLIMAGETEXTURELOADER_H
