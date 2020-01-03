//
// Created by paul on 06.01.19.
//

#include "paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h"

namespace PAX {
    PAX_PROPERTY_INIT(PAX::VelocityBehaviour2D, PAX_PROPERTY_IS_CONCRETE)

    VelocityBehaviour2D * VelocityBehaviour2D::createFromProvider(ContentProvider & provider) {
        return new VelocityBehaviour2D();
    }

    void VelocityBehaviour2D::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);

        if (auto vec = provider.get<glm::vec2>("velocity")) {
            this->velocity = vec.value();
        }

        if (auto angle = provider.get<float>("angularVelocity")) {
            this->angularVelocityInDegrees = angle.value();
        }
    }

    void VelocityBehaviour2D::update(UpdateOptions & options) {
        Transformation& t = getOwner()->getTransformation();
        t.position2D() += velocity * options.dt;
        t.setRotation2DInDegrees(
                t.getRotation2DInDegrees() + angularVelocityInDegrees * options.dt
        );
    }
}