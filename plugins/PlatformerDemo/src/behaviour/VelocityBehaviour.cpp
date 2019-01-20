//
// Created by paul on 06.01.19.
//

#include "platformerdemo/behaviour/VelocityBehaviour.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::VelocityBehaviour, PAX_PROPERTY_IS_CONCRETE)

    VelocityBehaviour * VelocityBehaviour::createFromProvider(ContentProvider & provider) {
        return new VelocityBehaviour();
    }

    void VelocityBehaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
        if (auto vec = provider.get<glm::vec2>("velocity")) {
            this->velocity = vec.value();
        }
    }

    void VelocityBehaviour::update() {
        Transformation& t = getOwner()->getTransformation();
        t.position2D() += velocity * Time::DeltaF;
    }
}