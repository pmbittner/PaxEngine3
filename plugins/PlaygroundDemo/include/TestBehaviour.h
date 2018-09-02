//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_DANCE2D_H
#define PAXENGINE3_DANCE2D_H

#include "utility/macros/MacroIncludes.h"
#include <core/entity/component/Behaviour.h>
#include <core/entity/Entity.h>

namespace PAX {
    class TestBehaviour : public Behaviour {
    PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)

    public:
        TestBehaviour() {}

        virtual void update() override {

        }
    };
}

#endif //PAXENGINE3_DANCE2D_H
