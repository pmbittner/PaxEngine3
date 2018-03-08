//
// Created by Paul on 03.02.2018.
//

#ifndef PAXENGINE3_SCALECHANGEDEVENT_H
#define PAXENGINE3_SCALECHANGEDEVENT_H

#include <glm/vec3.hpp>
#include "EntityEvent.h"

namespace PAX {
    struct ScaleChangedEvent : public EntityEvent {
        union {
            const glm::vec2 oldScale2D;
            const glm::vec3 oldScale;
        };
        union {
            const glm::vec2 newScale2D;
            const glm::vec3 newScale;
        };

        ScaleChangedEvent(Entity *entity, const glm::vec3 &oldScale, const glm::vec3 &newScale)
                : EntityEvent(entity), oldScale(oldScale), newScale(newScale)
        {
        }
    };
}

#endif //PAXENGINE3_SCALECHANGEDEVENT_H
