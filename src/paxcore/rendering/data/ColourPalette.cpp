//
// Created by Paul Bittner on 11.04.2020.
//

#include <paxcore/rendering/data/ColourPalette.h>

namespace PAX {
    ColourPalette::~ColourPalette() = default;

    Colour ColourPalette::getNext() {
        return getColourAt(current++);
    }

    Colour ColourPalette::getColourAt(size_t index) {
        return get(index);
    }

    RandomColourPalette::RandomColourPalette() : rng(), distribution(0, 255) {}

    RandomColourPalette::~RandomColourPalette() = default;

    Colour RandomColourPalette::get(size_t index) {
        return {distribution(rng), distribution(rng), distribution(rng), 255};
    }
}