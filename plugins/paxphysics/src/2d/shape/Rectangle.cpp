//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/shape/Rectangle.h>

namespace PAX::Physics {
    Rectangle::Rectangle(const glm::vec2 & size) : Shape2D() {
        aabb = FloatBoundingBox2D(size);
    }

    Rectangle::~Rectangle() = default;
}