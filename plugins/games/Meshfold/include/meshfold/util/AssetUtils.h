//
// Created by Paul Bittner on 13.04.2020.
//

#ifndef PAXENGINE3_ASSETUTILS_H
#define PAXENGINE3_ASSETUTILS_H

#include "paxcore/rendering/data/Asset.h"

namespace PAX::AssetUtils {
    Mesh* getFirstMeshYouCanFind(const std::shared_ptr<Asset> & asset);
    std::shared_ptr<Texture> getFirstTextureYouCanFind(const std::shared_ptr<Asset> & asset);
    void setAllDiffuseTextures(const std::shared_ptr<Asset> & asset, const std::shared_ptr<Texture> & texture);
}

#endif //PAXENGINE3_ASSETUTILS_H
