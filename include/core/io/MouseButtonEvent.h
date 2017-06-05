//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOUSEBUTTONEVENT_H
#define PAXENGINE3_MOUSEBUTTONEVENT_H

#include "../event/Event.h"
#include "Mouse.h"

namespace PAX {
    class MouseButtonEvent : public Event {
    public:
        Mouse *mouse;
        int button;
    };
}

#endif //PAXENGINE3_MOUSEBUTTONEVENT_H
