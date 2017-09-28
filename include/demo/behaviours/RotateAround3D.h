//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_ROTATEAROUND_H
#define PAXENGINE3_ROTATEAROUND_H

#include "../../core/entity/component/Behaviour.h"
#include "../../core/entity/Entity.h"

namespace PAX {
    class RotateAround3D : public Behaviour {
        glm::vec3 _impulse;
    public:
        RotateAround3D(glm::vec3 impulse = glm::vec3(0.01f, 0.008f, 0.006f)) : _impulse(impulse){
        }

        virtual void update() override {
            Transform &t = getOwner()->getTransform();
            glm::vec3 rotation = t.getRotation3D();
            rotation += _impulse;
            t.setRotation(rotation);
        }
    };
}

#endif //PAXENGINE3_ROTATEAROUND_H
