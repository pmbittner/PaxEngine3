//
// Created by Bittner on 21/06/2019.
//

#ifndef PAXENGINE3_WORLDSIZE_H
#define PAXENGINE3_WORLDSIZE_H

#include <paxcore/world/WorldProperty.h>

namespace PAX {
    class WorldSize : public WorldProperty {
        PAX_PROPERTY(WorldSize, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        /// width, height and depth of the layer
        /// Negative values denote an unbound, i.e., infinite dimension.
        union {
            glm::vec2 size2D;
            glm::vec3 size;
        };

    public:
        explicit WorldSize(const glm::vec3 & size = {-1.f, -1.f, -1.f});

        PAX_NODISCARD const glm::vec3 & getSize() const;
        PAX_NODISCARD const glm::vec2 & getSize2D() const;
        void setSize(const glm::vec3& size);
        void setSize2D(const glm::vec2& size);

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_WORLDSIZE_H
