//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_MOUSEWHEELEVENT_H
#define PAXENGINE3_MOUSEWHEELEVENT_H

#include "MouseEvent.h"

namespace PAX {
    struct MouseWheelEvent : public MouseEvent {
    public:    
        int ticksX = 0; /**< The amount scrolled horizontally, positive to the right and negative to the left */
        int ticksY = 0; /**< The amount scrolled vertically, positive away from the user (up) and negative toward the user (down) */
    };
}

#endif //PAXENGINE3_MOUSEWHEELEVENT_H
