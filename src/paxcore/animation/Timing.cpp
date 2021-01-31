//
// Created by Paul Bittner on 31.01.2021.
//

#include <cmath>
#include <paxcore/animation/Timing.h>

namespace PAX::Time {
    Timespan Modulo(Timespan lhs, Timespan rhs) {
        return Timespan(std::fmod(lhs.count(), rhs.count()));
    }
}