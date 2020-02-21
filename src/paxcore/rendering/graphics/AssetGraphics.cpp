//
// Created by Paul on 02.09.2018.
//

#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxutil/reflection/EngineFieldFlags.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::AssetGraphics)

    AssetGraphics::AssetGraphics() = default;

    ClassMetadata AssetGraphics::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add({"asset", paxtypeof(_asset), &_asset, Field::IsMandatory | EngineFieldFlags::IsResource});
        return m;
    }

    AssetGraphics::AssetGraphics(const std::shared_ptr<PAX::Asset> &asset) : _asset(asset) {

    }

    void AssetGraphics::render(PAX::RenderOptions &renderOptions) {
        Super::render(renderOptions);
        _asset->render(renderOptions);
    }
}