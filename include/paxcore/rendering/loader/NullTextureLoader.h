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

        bool canLoad(Path path) const override;
        std::shared_ptr<Texture> load(Path path) override;
        std::shared_ptr<Texture> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters) override;
    };
}

#endif //PAXENGINE3_NULLTEXTURELOADER_H
