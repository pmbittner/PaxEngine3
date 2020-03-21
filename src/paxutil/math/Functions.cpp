//
// Created by Paul Bittner on 21.03.2020.
//
#include <paxutil/math/Functions.h>
#include <math.h>

namespace PAX::Math {
    glm::vec2 angleToDirection(float angleInRadians) {
        return {cos(angleInRadians), sin(angleInRadians)};
    }

    float directionToRadians(const glm::vec2 & direction) {
        return atan2(direction.y, direction.x);
    }
}