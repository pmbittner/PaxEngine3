//
// Created by Paul Bittner on 11.04.2020.
//

#ifndef PAXENGINE3_COLOURPALETTE_H
#define PAXENGINE3_COLOURPALETTE_H

#include "Colour.h"
#include <random>

namespace PAX {
    class ColourPalette {
        size_t current = 0;

    protected:
        virtual Colour get(size_t index) = 0;

    public:
        virtual ~ColourPalette() = 0;
        PAX_NODISCARD Colour getNext();
        PAX_NODISCARD Colour getColourAt(size_t index);
    };

    class RandomColourPalette : public ColourPalette {
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> distribution;

    public:
        RandomColourPalette();

        ~RandomColourPalette() override;
        Colour get(size_t index) override;
    };
}

#endif //PAXENGINE3_COLOURPALETTE_H
