//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOUSEBUTTONEVENT_H
#define PAXENGINE3_MOUSEBUTTONEVENT_H

#include "MouseEvent.h"
#include <core/io/MouseButtons.h>

namespace PAX {
    struct MouseButtonEvent : public MouseEvent {
    public:
        MouseButton button = MouseButton::NONE;
    };
}

#endif //PAXENGINE3_MOUSEBUTTONEVENT_H
