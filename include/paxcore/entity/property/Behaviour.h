//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOUR_H
#define PAXENGINE3_BEHAVIOUR_H

#include "paxcore/entity/EntityProperty.h"

namespace PAX {
    class Behaviour : public EntityProperty {
        PAX_PROPERTY(Behaviour, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(EntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

    public:
        virtual void update();
    };
}

#endif //PAXENGINE3_BEHAVIOUR_H
