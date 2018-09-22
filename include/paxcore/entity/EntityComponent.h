//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <paxutil/property/Property.h>
#include "Entity.h"

namespace PAX {
    typedef Property<Entity> EntityComponent;
}

#define PAX_ENTITYCOMPONENT_BODY(Parent, bool_multiple) PAX_PROPERTY_BODY(Parent, bool_multiple)

#define PAX_ENTITYCOMPONENT_DEPENDS_ON(...) PAX_PROPERTY_DEPENDS_ON(__VA_ARGS__)

#endif //PAXENGINE3_ENTITYCOMPONENT_H
