//
// Created by Paul on 30.12.2018.
//

#ifndef PAXENGINE3_PROPERTYREMOVEDEVENT_H
#define PAXENGINE3_PROPERTYREMOVEDEVENT_H

#include "PropertyContainerEvent.h"

namespace PAX {
    template <typename C, class Prop>
    struct PropertyDetachedEvent : public PropertyContainerEvent<C> {
        Prop * property;

        PropertyDetachedEvent(Prop* prop, PropertyContainer<C>* container)
                : PropertyContainerEvent<C>(container), property(prop) {}
    };
}

#endif //PAXENGINE3_PROPERTYREMOVEDEVENT_H
