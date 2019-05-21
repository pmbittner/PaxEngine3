//
// Created by paul on 06.01.19.
//

#include "paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::VelocityBehaviour2D, PAX_PROPERTY_IS_CONCRETE)

    VelocityBehaviour2D * VelocityBehaviour2D::createFromProvider(ContentProvider & provider) {
        return new VelocityBehaviour2D();
    }

    void VelocityBehaviour2D::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
        if (auto vec = provider.get<glm::vec2>("velocity")) {
            this->velocity = vec.value();
        }
    }

    void VelocityBehaviour2D::update() {
        Transformation& t = getOwner()->getTransformation();
        t.position2D() += velocity * Time::DeltaF;
    }
}