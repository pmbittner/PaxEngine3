//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_DANCE2D_H
#define PAXENGINE3_DANCE2D_H

#include <paxutil/macros/MacroIncludes.h>
#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/Entity.h>

namespace PAX {
    class TestBehaviour : public Behaviour {
    PAX_PROPERTY_DERIVES(PAX::Behaviour)
    PAX_PROPERTY_IS_SINGLE

    public:
        TestBehaviour() {}

        virtual void update() override {

        }
    };
}

#endif //PAXENGINE3_DANCE2D_H
