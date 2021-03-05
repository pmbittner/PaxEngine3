//
// Created by Paul Bittner on 05.03.2021.
//

#include <polypropylene/log/Errors.h>
#include "paxcore/animation/AnimationBehaviour.h"

std::ostream & operator<<(std::ostream & str, const PAX::AnimationBehaviour & ab) {
    switch (ab) {
        case PAX::AnimationBehaviour::ONCE: return str << "ONCE";
        case PAX::AnimationBehaviour::LOOP: return str << "LOOP";
        case PAX::AnimationBehaviour::PINGPONG: return str << "PINGPONG";
        default: PAX_NOT_IMPLEMENTED_EXCEPTION();
    }
}