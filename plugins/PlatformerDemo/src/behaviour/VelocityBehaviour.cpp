//
// Created by paul on 06.01.19.
//

#include <behaviour/VelocityBehaviour.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::VelocityBehaviour)

    void VelocityBehaviour::update() {
        Transformation& t = getOwner()->getTransformation();
        t.position2D() += velocity * Time::DeltaF;
    }
}