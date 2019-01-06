//
// Created by Paul on 19.01.2018.
//

#ifndef PAXENGINE3_VELOCITYBEHAVIOUR_H
#define PAXENGINE3_VELOCITYBEHAVIOUR_H


#include <paxcore/entity/EntityComponent.h>
#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/time/Time.h>
#include <paxutil/property/PropertyContainerPrefab.h>

namespace PAX {
    class VelocityBehaviour : public Behaviour {
        PAX_PROPERTY(VelocityBehaviour)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

    public:
        glm::vec2 velocity = glm::vec2(0);
        std::string test = "Morgenroete";

        void update() override;
    };
}

#endif //PAXENGINE3_VELOCITYBEHAVIOUR_H
