//
// Created by Paul Bittner on 21.03.2020.
//

#include <meshfold/Portal.h>

namespace PAX {
    Portal::Portal() : from(0), to(0), target(0) {}

    Portal::Portal(const glm::vec2 &from, const glm::vec2 &to, size_t target)
    : from(from), to(to), target(target) {

    }

    static inline float cross2d(const glm::vec2 & a, const glm::vec2 & b) {
        return a.x * b.y - a.y * b.x;
    }

    glm::vec2 Portal::intersect(const glm::vec2 &p, const glm::vec2 &d, bool& parallel) const {
        const glm::vec2 me = to - from;
        float down = cross2d(me, d);

        if (down == 0) {
            parallel = true;
            return {0, 0};
        }

        parallel = false;

        return glm::vec2(cross2d(p - from, d) / down, cross2d(p - from, me) / down);
    }

    glm::vec2 Portal::normal() const {
        auto axis = glm::normalize(glm::vec2(to - from));
        return direction * glm::vec2(axis.y, -axis.x);
    }

    glm::mat2 Portal::space() const {
        return {glm::normalize(to - from), normal()};
    }
}