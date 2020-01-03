//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SIZE_H
#define PAXENGINE3_SIZE_H

#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxcore/gameentity/event/ScaleChangedEvent.h>
#include <paxutil/math/BoundingBox.h>

namespace PAX {
    class Size : public GameEntityProperty {
        PAX_PROPERTY(Size, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        union {
            glm::vec2 size2D;
            glm::vec3 size = glm::vec3(0);
        };

    public:
        explicit Size(const glm::vec3& size);

        void attached(GameEntity& entity) override;

        void setSize(const glm::vec3& size);
        void setSize2D(const glm::vec2& size);

        PAX_NODISCARD float getWidth() const;
        PAX_NODISCARD float getHeight() const;
        PAX_NODISCARD float getDepth() const;
        PAX_NODISCARD glm::vec3 getSize() const;
        PAX_NODISCARD glm::vec2 getSize2D() const;

        PAX_NODISCARD FloatBoundingBox3D toBoundingBox() const;

        /**
         * Also considers all children of the owning entity.
         * @return
         */
        PAX_NODISCARD FloatBoundingBox3D toAbsoluteBoundingBox() const;

        PAX_NODISCARD glm::vec3 getSizeUnscaled() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}
#endif //PAXENGINE3_SIZE_H
