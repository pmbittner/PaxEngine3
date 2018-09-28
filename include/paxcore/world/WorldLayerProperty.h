//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_WORLDLAYERPROPERTY_H
#define PAXENGINE3_WORLDLAYERPROPERTY_H

#include <paxutil/property/Property.h>
#include "WorldLayer.h"

namespace PAX {
    typedef Property<WorldLayer> WorldLayerProperty;
}

#define PAX_WORLDLAYERPROPERTY_BODY(Parent, bool_multiple) PAX_PROPERTY_BODY(Parent, bool_multiple)

#define PAX_WORLDLAYERPROPERTY_DEPENDS_ON(...) PAX_PROPERTY_DEPENDS_ON(__VA_ARGS__)

#endif //PAXENGINE3_WORLDLAYERPROPERTY_H
