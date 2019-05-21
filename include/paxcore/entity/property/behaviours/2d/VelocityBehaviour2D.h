//
// Created by Paul on 19.01.2018.
//

#ifndef PAXENGINE3_VELOCITYBEHAVIOUR2D_H
#define PAXENGINE3_VELOCITYBEHAVIOUR2D_H


#include <paxcore/entity/EntityProperty.h>
#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/time/Time.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>

namespace PAX {
    class VelocityBehaviour2D : public Behaviour {
        PAX_PROPERTY(VelocityBehaviour2D, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

    public:
        glm::vec2 velocity = glm::vec2(0);

        void update() override;
    };
}

#endif //PAXENGINE3_VELOCITYBEHAVIOUR2D_H
