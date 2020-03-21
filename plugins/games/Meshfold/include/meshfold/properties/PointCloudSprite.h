//
// Created by Paul Bittner on 18.03.2020.
//

#ifndef PAXENGINE3_POINTCLOUDSPRITE_H
#define PAXENGINE3_POINTCLOUDSPRITE_H

#include "paxcore/rendering/Graphics.h"
#include "paxcore/rendering/scenegraph/nodes/MeshNode.h"
#include "paxcore/rendering/scenegraph/nodes/TexturingNode.h"
#include <paxcore/rendering/data/Image.h>

namespace PAX {
    class MeshfoldSystem;

    class PointCloudSprite : public Graphics {
        PAX_PROPERTY(PointCloudSprite, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

        friend MeshfoldSystem;

        std::vector<glm::vec2> originalpositions;
        std::vector<glm::vec2> positions;
        std::vector<glm::vec2> uvs;

        std::shared_ptr<Texture> texture;
        TexturingNode textureNode;
        MeshNode meshNode;

        PointCloudSprite();
        void init();

    public:
        float pointSize = 1;

        PointCloudSprite(const std::shared_ptr<Texture> & texture);

        void render(RenderOptions& options) override;

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
    };
}

#endif //PAXENGINE3_POINTCLOUDSPRITE_H
