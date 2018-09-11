//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_DANCE2D_H
#define PAXENGINE3_DANCE2D_H

#include <paxutil/math/MathDefines.h>
#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/entity/Entity.h>

namespace PAX {
    class Dance2D : public Behaviour {
    PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, true)

        float _t = 0;
        float _speed = 0, _maxAngle = 0, _maxElongation = 0;

    public:
        Dance2D(float speed = 0.03f, float maxAngle = M_PI/4, float maxElongation = -50) : _speed(speed), _maxAngle(maxAngle), _maxElongation(maxElongation) {}

        virtual void update() override {
            float anim = std::sin(_t);
            float position = anim * _maxElongation;
            float rotation = anim * _maxAngle;

            Transformation &t = getOwner()->getTransformation();
            t.setRotation(0, 0, rotation);
            //t.setX(position);

            _t = fmod(_t + _speed, 2*M_PI);
        }
    };
}

#endif //PAXENGINE3_DANCE2D_H
