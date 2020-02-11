//
// Created by Paul on 30.08.2018.
//

#ifndef PAXENGINE3_ASSIMPRESOURCELOADER_H
#define PAXENGINE3_ASSIMPRESOURCELOADER_H

#include <paxcore/rendering/data/Asset.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    namespace AssetImport {
        class AssimpResourceLoader : public ResourceLoader<Asset, Path> {
        public:
            AssimpResourceLoader() = default;

            PAX_NODISCARD bool canLoad(Path p) const override;
            PAX_NODISCARD std::shared_ptr<Asset> load(Path p) override;
            PAX_NODISCARD std::shared_ptr<Asset> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
        };
    }
}
#endif //PAXENGINE3_ASSIMPRESOURCELOADER_H
