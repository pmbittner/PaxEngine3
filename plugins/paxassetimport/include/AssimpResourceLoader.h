//
// Created by Paul on 30.08.2018.
//

#ifndef PAXENGINE3_ASSIMPRESOURCELOADER_H
#define PAXENGINE3_ASSIMPRESOURCELOADER_H

#include <paxcore/rendering/data/Asset.h>
#include <paxcore/io/resources/ResourceLoader.h>

namespace PAX {
    namespace AssetImport {
        class AssimpResourceLoader : public ResourceLoader<Asset, Path> {
        public:
            AssimpResourceLoader() = default;

            virtual bool canLoad(Path p) const override;
            virtual std::shared_ptr<Asset> load(Path p) override;
        };
    }
}
#endif //PAXENGINE3_ASSIMPRESOURCELOADER_H
