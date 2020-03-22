//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_PORTAL_H
#define PAXENGINE3_PORTAL_H

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    struct Portal {
        glm::vec2 from, to;
        Portal * target = nullptr;

        Portal();
        Portal(const glm::vec2 & from, const glm::vec2 & to, Portal * target = nullptr);

        /**
         * Returns a factor "s" such that the ray "p+d" intersects this portal at "from + s*(target - from)"
         * @param parallel is set to true if the ray is parallel to this portal.
         */
        PAX_NODISCARD float intersect(const glm::vec2 & p, const glm::vec2 & d, bool& parallel) const;
        PAX_NODISCARD glm::vec2 normal() const;
        PAX_NODISCARD glm::mat2 space() const;
    };
}

#endif //PAXENGINE3_PORTAL_H
