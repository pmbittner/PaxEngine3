//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SIZECHANGEDEVENT_H
#define PAXENGINE3_SIZECHANGEDEVENT_H

#include <glm/vec3.hpp>
#include "EntityEvent.h"

namespace PAX {
    class Size;

    struct SizeChangedEvent : public EntityEvent {
        union {
            const glm::vec2 oldSize2D;
            const glm::vec3 oldSize;
        };

        Size *size;

        SizeChangedEvent(Entity *entity, const glm::vec3 &oldSize, Size *size)
                : EntityEvent(entity), oldSize(oldSize), size(size)
        {
        }
    };
}

#endif //PAXENGINE3_SIZECHANGEDEVENT_H
