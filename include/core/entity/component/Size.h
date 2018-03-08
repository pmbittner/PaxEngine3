//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SIZE_H
#define PAXENGINE3_SIZE_H

#include <core/entity/EntityComponent.h>
#include <core/entity/event/ScaleChangedEvent.h>
#include <glm/glm.hpp>

namespace PAX {
    PAX_ENTITYCOMPONENT(Size, EntityComponent, false)
    class Size : public EntityComponent {
        PAX_ENTITYCOMPONENT_BODY

        union {
            glm::vec2 _size2D;
            glm::vec3 _size;
        };

    public:
        Size(const glm::vec3& size);

        virtual void attached(Entity* entity);

        void setSize(const glm::vec3& size);
        void setSize2D(const glm::vec2& size);

        float getWidth() const;
        float getHeight() const;
        float getDepth() const;
        glm::vec3 getSize() const;
        glm::vec2 getSize2D() const;

        glm::vec3 getSizeUnscaled() const;
    };
}
#endif //PAXENGINE3_SIZE_H
