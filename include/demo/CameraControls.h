//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_CAMERACONTROLS_H
#define PAXENGINE3_CAMERACONTROLS_H

#include "../core/entity/component/Behaviour.h"
#include "../core/entity/Entity.h"
#include "../core/Engine.h"

namespace PAX {
    class CameraControls : public Behaviour {
        float speed = 0.02f;
        float rotspeed = 0.01f;

    public:
        CameraControls() {}

        virtual void update() override {
            glm::vec3 move;
            glm::vec3 rot;

            Keyboard *keyboard = Engine::GetInstance()->getInputSystem()->getKeyboard();

            if (keyboard->isKeyDown(SDL_SCANCODE_W)) {
                move.z -= speed;
            }
            if (keyboard->isKeyDown(SDL_SCANCODE_S)) {
                move.z += speed;
            }
            if (keyboard->isKeyDown(SDL_SCANCODE_A)) move.x -= speed;
            if (keyboard->isKeyDown(SDL_SCANCODE_D)) move.x += speed;

            if (keyboard->isKeyDown(SDL_SCANCODE_LEFT)) rot.y -= rotspeed;
            if (keyboard->isKeyDown(SDL_SCANCODE_RIGHT)) rot.y += rotspeed;

            Transform &t = getOwner()->getTransform();
            t.setPosition(t.xyz() + move);
            t.setRotation(t.getRotation3D() + rot);
        }
    };
}

#endif //PAXENGINE3_CAMERACONTROLS_H
