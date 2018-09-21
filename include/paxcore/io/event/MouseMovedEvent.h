//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_MOUSEMOVEDEVENT_H
#define PAXENGINE3_MOUSEMOVEDEVENT_H

#include "MouseEvent.h"
#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    struct MouseMovedEvent : public MouseEvent {
    public:
        glm::ivec2 oldScreenPos;
    };
}

#endif //PAXENGINE3_MOUSEMOVEDEVENT_H
