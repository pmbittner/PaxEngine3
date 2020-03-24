//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_PORTAL_H
#define PAXENGINE3_PORTAL_H

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    struct Portal {
        static constexpr const int LEFT  = -1;
        static constexpr const int RIGHT = +1;

        glm::vec2 from, to;
        int direction = RIGHT;
        Portal * target = nullptr;

        Portal();
        Portal(const glm::vec2 & from, const glm::vec2 & to, Portal * target = nullptr);

        /**
         * Returns a factor
         * "x" such that the ray "p+d" intersects this portal at "from + x*(target - from)" and
         * "y" such that the ray "p+d" intersects this portal at "p + y*d".
         * @param parallel is set to true if the ray is parallel to this portal.
         */
        PAX_NODISCARD glm::vec2 intersect(const glm::vec2 & p, const glm::vec2 & d, bool& parallel) const;
        PAX_NODISCARD glm::vec2 normal() const;
        PAX_NODISCARD glm::mat2 space() const;
    };
}

#endif //PAXENGINE3_PORTAL_H
