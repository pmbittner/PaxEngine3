//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_COLOUR_H
#define PAXENGINE3_COLOUR_H

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    using Colour = glm::vec<4, char, glm::defaultp>;

    namespace Colours {
        static constexpr const Colour Red = Colour(255, 0, 0, 255);
        static constexpr const Colour Green = Colour(0, 255, 0, 255);
        static constexpr const Colour Blue = Colour(0, 0, 255, 255);
    }
}

#endif //PAXENGINE3_COLOUR_H
