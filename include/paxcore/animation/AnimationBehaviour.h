//
// Created by Paul Bittner on 31.01.2021.
//

#ifndef MESHFOLD_ANIMATIONBEHAVIOUR_H
#define MESHFOLD_ANIMATIONBEHAVIOUR_H

#include <ostream>

namespace PAX {
    enum class AnimationBehaviour {
        ONCE,
        LOOP,
        PINGPONG
    };
}

std::ostream & operator<<(std::ostream & str, const PAX::AnimationBehaviour & ab);

#endif //MESHFOLD_ANIMATIONBEHAVIOUR_H
