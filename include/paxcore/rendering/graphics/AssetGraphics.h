//
// Created by Paul on 02.09.2018.
//

#ifndef PAXENGINE3_ASSETGRAPHICS_H
#define PAXENGINE3_ASSETGRAPHICS_H

#include <paxcore/rendering/data/Asset.h>
#include "../Graphics.h"

namespace PAX {
    class AssetGraphics : public Graphics {
        PAX_ENTITYCOMPONENT_BODY(Graphics, false)

    protected:
        std::shared_ptr<Asset> _asset;

    public:
        AssetGraphics(const std::shared_ptr<Asset> & asset);

        virtual void setShader(std::shared_ptr<Shader> &shader) override;
        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_ASSETGRAPHICS_H