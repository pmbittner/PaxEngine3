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

        bool canLoad(Path path) const override;
        std::shared_ptr<Texture> load(Path path) override;
        std::shared_ptr<Texture> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters) override;
    };
}

#endif //PAXENGINE3_SDLIMAGETEXTURELOADER_H
