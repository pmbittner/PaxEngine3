//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SIZE_H
#define PAXENGINE3_SIZE_H

#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/entity/EntityComponent.h>
#include <paxcore/entity/event/ScaleChangedEvent.h>
#include <paxutil/math/BoundingBox.h>

namespace PAX {
    class Size : public EntityComponent {
        PAX_PROPERTY_DERIVES(EntityComponent)
        PAX_PROPERTY_IS_SINGLE

        union {
            glm::vec2 _size2D;
            glm::vec3 _size;
        };

    public:
        Size(const glm::vec3& size);

        virtual void attached(Entity& entity) override;

        void setSize(const glm::vec3& size);
        void setSize2D(const glm::vec2& size);

        float getWidth() const;
        float getHeight() const;
        float getDepth() const;
        glm::vec3 getSize() const;
        glm::vec2 getSize2D() const;

        FloatBoundingBox3D toBoundingBox();
        FloatBoundingBox3D toAbsoluteBoundingBox();

        glm::vec3 getSizeUnscaled() const;
    };
}
#endif //PAXENGINE3_SIZE_H
