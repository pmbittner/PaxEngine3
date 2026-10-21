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

    // Declared in the namespace of the enum, so that argument-dependent lookup finds it.
    std::ostream & operator<<(std::ostream & str, const AnimationBehaviour & ab);
}

#endif //MESHFOLD_ANIMATIONBEHAVIOUR_H
