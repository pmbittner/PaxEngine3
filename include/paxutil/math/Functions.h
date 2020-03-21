//
// Created by Paul on 20.01.2018.
//

#ifndef PAXENGINE3_FUNCTIONS_H
#define PAXENGINE3_FUNCTIONS_H

#include "../lib/GlmIncludes.h"

namespace PAX {
    namespace Math {
        template <typename T>
        int sign(T val) {
            return (T(0) < val) - (val < T(0));
        }

        template<typename T>
        T clamp(T value, T min, T max) {
            return std::max(std::min(value, max), min);
        }

        glm::vec2 angleToDirection(float angleInRadians);
        float directionToRadians(const glm::vec2 & direction);
    }
}

#endif //PAXENGINE3_FUNCTIONS_H
