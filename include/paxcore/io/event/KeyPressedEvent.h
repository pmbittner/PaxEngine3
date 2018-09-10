//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_KEYPRESSEDEVENT_H
#define PAXENGINE3_KEYPRESSEDEVENT_H

#include "KeyEvent.h"

namespace PAX {
    struct KeyPressedEvent : public KeyEvent {
        bool repeated = false;
    };
}

#endif //PAXENGINE3_KEYPRESSEDEVENT_H
