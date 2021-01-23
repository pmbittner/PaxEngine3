//
// Created by Paul Bittner on 23.01.2021.
//

#include <paxphysics/2d/gravityfields/SphereGravityField.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(SphereGravityField)

    SphereGravityField::SphereGravityField() : SphereGravityField(0, 0) {}

    SphereGravityField::SphereGravityField(float intensity, float radius)
    : GravityField(intensity), radius(radius) {}

    bool SphereGravityField::isInside(const glm::vec2 &point) const {
        const GameEntity * e = getOwner();
        if (e) {
            // avoid sqrt by squaring each side of the equation
            // Performance: cache radius*radius?
            return glm::length2(e->getTransformation().position2D() - point) <= radius*radius;
        }
        return false;
    }

    glm::vec2 SphereGravityField::getFallingDirection(const glm::vec2 &point) const {
        const GameEntity * e = getOwner();
        if (e && isInside(point)) {
            return getIntensity() * (e->getTransformation().position2D() - point);
        }
        return glm::vec2(0);
    }

    void SphereGravityField::setRadius(float radius) {
        this->radius = radius;
    }

    float SphereGravityField::getRadius() const {
        return radius;
    }
}