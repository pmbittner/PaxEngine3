//
// Created by Paul on 19.01.2018.
//

#ifndef PAXENGINE3_MOVEMENT2D_H
#define PAXENGINE3_MOVEMENT2D_H


#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxcore/gameentity/property/Behaviour.h>

namespace PAX {
    class Movement2D : public Behaviour {
        PAX_PROPERTY(Movement2D, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE

    public:
        glm::vec2 velocity = glm::vec2(0);
        float angularVelocityInDegrees = 0;

        void update(UpdateOptions & options) override;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_MOVEMENT2D_H
