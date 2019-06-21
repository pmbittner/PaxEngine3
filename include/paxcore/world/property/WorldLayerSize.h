//
// Created by Bittner on 21/06/2019.
//

#ifndef PAXENGINE3_WORLDLAYERSIZE_H
#define PAXENGINE3_WORLDLAYERSIZE_H

#include <paxcore/world/WorldLayerProperty.h>

namespace PAX {
    class WorldLayerSize : public WorldLayerProperty {
        PAX_PROPERTY(WorldLayerSize, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldLayerProperty)
        PAX_PROPERTY_IS_SINGLE

        /// width, height and depth of the layer
        /// Negative values denote an unbound, i.e., infinite dimension.
        union {
            glm::vec2 size2D;
            glm::vec3 size;
        };

    public:
        explicit WorldLayerSize(const glm::vec3 & size = {-1.f, -1.f, -1.f});
        explicit WorldLayerSize(const glm::vec2 & size = {-1.f, -1.f});

        const glm::vec3 & getSize() const;
        const glm::vec2 & getSize2D() const;
        void setSize(const glm::vec3& size);
        void setSize2D(const glm::vec2& size);
    };
}

#endif //PAXENGINE3_WORLDLAYERSIZE_H
