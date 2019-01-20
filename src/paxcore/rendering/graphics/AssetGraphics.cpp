//
// Created by Paul on 02.09.2018.
//

#include <paxcore/rendering/graphics/AssetGraphics.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::AssetGraphics, PAX_PROPERTY_IS_CONCRETE)

    AssetGraphics * AssetGraphics::createFromProvider(PAX::ContentProvider & provider) {
        return new AssetGraphics(provider.requireResource<Asset>("asset"));
    }

    void AssetGraphics::initializeFromProvider(PAX::ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    AssetGraphics::AssetGraphics(const std::shared_ptr<PAX::Asset> &asset) : _asset(asset) {

    }

    void AssetGraphics::render(PAX::RenderOptions &renderOptions) {
        Super::render(renderOptions);
        _asset->render(renderOptions);
    }
}