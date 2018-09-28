//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_WORLDLAYERPROPERTYREMOVEDEVENT_H
#define PAXENGINE3_WORLDLAYERPROPERTYREMOVEDEVENT_H

#include "WorldLayerEvent.h"

namespace PAX {
    template <class Prop>
    struct WorldLayerPropertyRemovedEvent : public WorldLayerEvent {
        const std::shared_ptr<Prop> & _property;

        WorldLayerPropertyRemovedEvent(
                const std::shared_ptr<Prop> & prop, WorldLayer* layer)
                : WorldLayerEvent(layer), _property(prop) {}
    };
}

#endif //PAXENGINE3_WORLDLAYERPROPERTYREMOVEDEVENT_H
