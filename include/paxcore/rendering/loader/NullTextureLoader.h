//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_NULLTEXTURELOADER_H
#define PAXENGINE3_NULLTEXTURELOADER_H

#include <paxcore/rendering/data/Texture.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    class NullTextureLoader : public ResourceLoader<Texture, Path> {
    private:
        // Cache texture here, so that it will never be deleted.
        std::shared_ptr<Texture> _texture = nullptr;

    public:
        NullTextureLoader();
        ~NullTextureLoader() override;

        PAX_NODISCARD bool canLoad(Path path) const override;
        PAX_NODISCARD std::shared_ptr<Texture> load(Path path) override;
        PAX_NODISCARD std::shared_ptr<Texture> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;

    };
}

#endif //PAXENGINE3_NULLTEXTURELOADER_H
