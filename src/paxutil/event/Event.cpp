//
// Created by Bittner on 03/07/2019.
//

#include <paxutil/event/Event.h>

namespace PAX {
    void Event::consume() {
        consumed = true;
    }

    bool Event::isConsumed() {
        return consumed;
    }
}