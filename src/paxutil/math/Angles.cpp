//
// Created by Paul on 10.09.2018.
//

#include <paxutil/math/Angles.h>

namespace PAX {
    namespace Math {
        glm::vec3 sphericalCoordinatesToDirection(float theta, float phi) {
            return {
                    std::sin(theta) * std::cos(phi),
                    std::sin(phi),
                    -std::cos(theta) * std::cos(phi)
            };
        }

        glm::vec2 lookDirToSphericalCoordinates(const glm::vec3 & lookdir) {
            auto theta = static_cast<float>(atan2(-lookdir.z, lookdir.x) - M_PI_2);
            auto phi   = static_cast<float>(M_PI_2 - std::acos(lookdir.y / glm::length(lookdir)));
            return {theta, phi};
        }

        glm::vec3 sphericalCoordinatesToUpDirection(float theta, float phi) {
            return glm::vec3(
                    -std::sin(theta) * std::sin(phi),
                    std::cos(phi),
                    std::cos(theta) * std::sin(phi)
            );
        }
    }
}