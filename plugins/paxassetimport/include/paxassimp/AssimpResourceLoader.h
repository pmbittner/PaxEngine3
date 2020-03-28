//
// Created by Paul on 30.08.2018.
//

#ifndef PAXENGINE3_ASSIMPRESOURCELOADER_H
#define PAXENGINE3_ASSIMPRESOURCELOADER_H

#include <paxcore/rendering/data/Asset.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    namespace AssetImport {
        using Flag = size_t;
        namespace Flags {
            constexpr const Flag None = 0;
            constexpr const Flag NoUpload = 1;
        }

        class AssimpResourceLoader : public ResourceLoader<Asset, Path, Flag> {
        public:
            AssimpResourceLoader() = default;

            PAX_NODISCARD bool canLoad(Path p, Flag f) const override;
            PAX_NODISCARD std::shared_ptr<Asset> load(Path p, Flag f) override;
            PAX_NODISCARD std::shared_ptr<Asset> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
        };
    }
}
#endif //PAXENGINE3_ASSIMPRESOURCELOADER_H
