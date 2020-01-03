//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_KEYEVENT_H
#define PAXENGINE3_KEYEVENT_H

#include <polypropylene/event/Event.h>
#include <paxcore/io/Keyboard.h>

namespace PAX {
    struct KeyEvent : public Event {
    public:
        Keyboard *keyboard = nullptr;
        Key button = Key::NONE;
    };
}

#endif //PAXENGINE3_KEYEVENT_H
