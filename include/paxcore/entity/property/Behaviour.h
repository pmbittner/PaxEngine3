//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOUR_H
#define PAXENGINE3_BEHAVIOUR_H

#include <paxcore/function/Updateable.h>
#include <paxcore/entity/EntityProperty.h>

namespace PAX {
    class Behaviour : public EntityProperty, public Updateable {
        PAX_PROPERTY(Behaviour, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(EntityProperty)
        PAX_PROPERTY_IS_MULTIPLE
    };
}

#endif //PAXENGINE3_BEHAVIOUR_H
