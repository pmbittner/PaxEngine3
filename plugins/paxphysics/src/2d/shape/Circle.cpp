//
// Created by Paul Bittner on 01.02.2021.
//

#include <paxphysics/2d/shape/Circle.h>

namespace PAX::Physics {
    Circle::Circle(float radius) : radius(radius) {
        const glm::vec2 aabbSize = glm::vec2(2) * radius;
        aabb = FloatBoundingBox2D(aabbSize);
    }

    Circle::~Circle() = default;

    float Circle::getRadius() const {
        return radius;
    }
}