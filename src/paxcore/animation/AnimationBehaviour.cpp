//
// Created by Paul Bittner on 05.03.2021.
//

#include <polypropylene/log/Errors.h>
#include "paxcore/animation/AnimationBehaviour.h"

namespace PAX {
    std::ostream & operator<<(std::ostream & str, const AnimationBehaviour & ab) {
        switch (ab) {
            case AnimationBehaviour::ONCE: return str << "ONCE";
            case AnimationBehaviour::LOOP: return str << "LOOP";
            case AnimationBehaviour::PINGPONG: return str << "PINGPONG";
            default: PAX_NOT_IMPLEMENTED_EXCEPTION();
        }
    }
}
