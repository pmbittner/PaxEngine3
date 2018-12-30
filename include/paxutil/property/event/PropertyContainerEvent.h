//
// Created by Paul on 30.12.2018.
//

#ifndef PAXENGINE3_PROPERTYCONTAINEREVENT_H
#define PAXENGINE3_PROPERTYCONTAINEREVENT_H

#include <paxutil/event/Event.h>

namespace PAX {
    template<typename C>
    class PropertyContainer;

    template<typename C>
    struct PropertyContainerEvent : public Event {
    public:
        C* container = nullptr;
        explicit PropertyContainerEvent(PropertyContainer<C>* container) : container(static_cast<C*>(container)) {}
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINEREVENT_H
