//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_DANCE2D_H
#define PAXENGINE3_DANCE2D_H

#include <paxutil/math/MathDefines.h>
#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/GameEntity.h>

namespace PAX {
    class Dance2D : public Behaviour {
        PAX_PROPERTY(Dance2D, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_MULTIPLE

        float _t = 0;
        float _speed = 0, _maxAngle = 0, _maxElongation = 0;

    public:
        explicit Dance2D(float speed = 0.03f, float maxAngle = M_PI/4, float maxElongation = -50) : _speed(speed), _maxAngle(maxAngle), _maxElongation(maxElongation) {}

        void update(UpdateOptions & options) override {
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
