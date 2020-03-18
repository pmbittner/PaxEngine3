//
// Created by Paul Bittner on 18.03.2020.
//

#ifndef PAXENGINE3_POINTCLOUDSPRITE_H
#define PAXENGINE3_POINTCLOUDSPRITE_H

#include "paxcore/rendering/Graphics.h"
#include "paxcore/rendering/scenegraph/nodes/MeshNode.h"
#include <paxcore/rendering/data/Image.h>

namespace PAX {
    class PointCloudSprite : public Graphics {
        PAX_PROPERTY(PointCloudSprite, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

        std::vector<glm::vec2> pixels;
        std::vector<glm::vec2> directions;
        std::shared_ptr<Image> image;

        MeshNode meshNode;

        PointCloudSprite();
        void init();

    public:
        PointCloudSprite(const std::shared_ptr<Image> & image);

        void render(RenderOptions& options) override;

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
    };
}

#endif //PAXENGINE3_POINTCLOUDSPRITE_H
