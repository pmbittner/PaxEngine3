//
// Created by paul on 11.09.18.
//

#ifndef PAXENGINE3_BASIS_H
#define PAXENGINE3_BASIS_H

#include "../lib/GlmIncludes.h"

namespace PAX {
    namespace Math {
        struct Basis {
            const glm::vec3 Forward;
            const glm::vec3 Up;
            const glm::vec3 Left;

            Basis(const glm::vec3 &forward, const glm::vec3 &up, const glm::vec3 &left) :
                    Forward(forward), Up(up), Left(left) {}
        };

        const Basis OpenGLBasis = Basis(
                {0, 0, -1},
                {0, 1, 0},
                {-1, 0, 0});
    }
}

#endif //PAXENGINE3_BASIS_H
