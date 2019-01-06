//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOUR_H
#define PAXENGINE3_BEHAVIOUR_H

#include "../EntityComponent.h"

namespace PAX {
    class Behaviour : public EntityComponent {
        PAX_PROPERTY(Behaviour)
        PAX_PROPERTY_DERIVES(EntityComponent)
        PAX_PROPERTY_IS_MULTIPLE

    public:
        virtual void update();
    };
}

#endif //PAXENGINE3_BEHAVIOUR_H
