//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOUSEBUTTONPRESSEDEVENT_H
#define PAXENGINE3_MOUSEBUTTONPRESSEDEVENT_H

#include "MouseButtonEvent.h"

namespace PAX {
    struct MouseButtonPressedEvent : public MouseButtonEvent {
        int clicks = 0;
    };
}

#endif //PAXENGINE3_MOUSEBUTTONPRESSEDEVENT_H
