//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SIZECHANGEDEVENT_H
#define PAXENGINE3_SIZECHANGEDEVENT_H

#include <glm/vec3.hpp>
#include "GameEntityEvent.h"

namespace PAX {
    class Size;

    struct SizeChangedEvent : public GameEntityEvent {
        union {
            const glm::vec2 oldSize2D;
            const glm::vec3 oldSize;
        };

        Size *size;

        SizeChangedEvent(GameEntity *entity, const glm::vec3 &oldSize, Size *size)
                : GameEntityEvent(entity), oldSize(oldSize), size(size)
        {
        }
    };
}

#endif //PAXENGINE3_SIZECHANGEDEVENT_H
