//
// Created by Paul on 02.09.2018.
//

#include <paxcore/rendering/graphics/AssetGraphics.h>

namespace PAX {
    AssetGraphics::AssetGraphics(const std::shared_ptr<PAX::Asset> &asset) : _asset(asset) {

    }

    void AssetGraphics::render(PAX::RenderOptions &renderOptions) {
        Super::render(renderOptions);
        _asset->render(renderOptions);
    }
}