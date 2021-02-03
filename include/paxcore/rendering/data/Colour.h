//
// Created by Paul Bittner on 21.03.2020.
//

#ifndef PAXENGINE3_COLOUR_H
#define PAXENGINE3_COLOUR_H

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    using Colour = glm::vec<4, unsigned char, glm::defaultp>;

    namespace Colours {
        const Colour Red = Colour(255, 0, 0, 255);
        const Colour Green = Colour(0, 255, 0, 255);
        const Colour Blue = Colour(0, 0, 255, 255);
        const Colour White = Colour(255, 255, 255, 255);
        const Colour Black = Colour(0, 0, 0, 255);
    }
}

#endif //PAXENGINE3_COLOUR_H
