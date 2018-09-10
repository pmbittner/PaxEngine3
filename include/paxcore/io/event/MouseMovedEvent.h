//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_MOUSEMOVEDEVENT_H
#define PAXENGINE3_MOUSEMOVEDEVENT_H

#include "MouseEvent.h"

namespace PAX {
    struct MouseMovedEvent : public MouseEvent {
    public:
        int oldX = 0, oldY = 0;
    };
}

#endif //PAXENGINE3_MOUSEMOVEDEVENT_H
