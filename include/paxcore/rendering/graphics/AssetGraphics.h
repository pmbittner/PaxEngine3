//
// Created by Paul on 02.09.2018.
//

#ifndef PAXENGINE3_ASSETGRAPHICS_H
#define PAXENGINE3_ASSETGRAPHICS_H

#include <paxcore/rendering/data/Asset.h>
#include "../Graphics.h"

namespace PAX {
    class AssetGraphics : public Graphics {
        PAX_PROPERTY(AssetGraphics)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

    protected:
        std::shared_ptr<Asset> _asset;

    public:
        AssetGraphics(const std::shared_ptr<Asset> & asset);

        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_ASSETGRAPHICS_H
