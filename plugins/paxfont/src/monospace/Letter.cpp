//
// Created by Paul Bittner on 07.03.2021.
//

#include <paxfont/monospace/Letter.h>

namespace PAX::Font {
    PAX_PROPERTY_IMPL(Letter)

    Letter::Letter() : Letter(0) {}
    Letter::Letter(char character) : character(character) {}

    ClassMetadata Letter::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(character));
        return m;
    }
}