//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_KEYBOARD_H
#define PAXENGINE3_KEYBOARD_H

// giosheo
#include "Keys.h"

namespace PAX {
    class Keyboard {
    public:
        virtual bool isKeyDown(Key key) = 0;
    };
}

#endif //PAXENGINE3_KEYBOARD_H
