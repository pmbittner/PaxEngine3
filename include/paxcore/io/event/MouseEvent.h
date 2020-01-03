//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_MOUSEEVENT_H
#define PAXENGINE3_MOUSEEVENT_H

#include <polypropylene/event/Event.h>
#include <paxcore/io/Mouse.h>

namespace PAX {
    struct MouseEvent : public Event {
    public:
        Mouse *mouse = nullptr;
    };
}

#endif //PAXENGINE3_MOUSEEVENT_H
