//
// Created by Paul on 19.01.2018.
//

#ifndef PAXENGINE3_VELOCITYBEHAVIOUR_H
#define PAXENGINE3_VELOCITYBEHAVIOUR_H


#include <paxcore/entity/EntityComponent.h>
#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/time/Time.h>
#include <paxutil/property/PropertyContainerPrefab.h>

template<class T, char const * name>
class Register {

};

constexpr char velocityName[]  = "VelocityBehaviour";

namespace PAX {

    class VelocityBehaviour : public Behaviour, private Register<VelocityBehaviour, velocityName> {
    PAX_PROPERTY_DERIVES(PAX::Behaviour)
    PAX_PROPERTY_IS_SINGLE
    PAX_PROPERTY_OPTIONAL(VelocityBehaviour, Entity)

    public:
        glm::vec2 velocity = glm::vec2(0);
        std::string test = "Morgenroete";

        void update() override;
    };
}

#endif //PAXENGINE3_VELOCITYBEHAVIOUR_H
