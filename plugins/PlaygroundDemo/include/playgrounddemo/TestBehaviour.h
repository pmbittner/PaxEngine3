//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_DANCE2D_H
#define PAXENGINE3_DANCE2D_H

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/GameEntity.h>

namespace PAX {
    class TestBehaviour : public Behaviour {
    PAX_PROPERTY_DERIVES(PAX::Behaviour)
    PAX_PROPERTY_IS_SINGLE

    public:
        TestBehaviour() = default;

        void update(UpdateOptions & options) override {

        }
    };
}

#endif //PAXENGINE3_DANCE2D_H
