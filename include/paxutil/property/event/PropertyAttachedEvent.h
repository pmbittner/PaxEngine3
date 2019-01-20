//
// Created by Paul on 30.12.2018.
//

#ifndef PAXENGINE3_PROPERTYADDEDEVENT_H
#define PAXENGINE3_PROPERTYADDEDEVENT_H

#include "PropertyContainerEvent.h"

namespace PAX {
    template <typename C, class Prop>
    struct PropertyAttachedEvent : public PropertyContainerEvent<C> {
        Prop * property;

        PropertyAttachedEvent(Prop* prop, PropertyContainer<C>* container)
                : PropertyContainerEvent<C>(container), property(prop) {}
    };
}

#endif //PAXENGINE3_PROPERTYADDEDEVENT_H
