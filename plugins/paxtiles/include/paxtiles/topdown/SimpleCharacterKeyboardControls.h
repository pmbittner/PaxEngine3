//
// Created by Paul on 21.05.2019.
//

#ifndef PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H
#define PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/service/Services.h>

#include "CharacterOrientation.h"

namespace PAX::Tiles {
    class SimpleCharacterKeyboardControls : public Behaviour {
        PAX_PROPERTY(SimpleCharacterKeyboardControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(VelocityBehaviour2D, CharacterOrientation)

        CharacterOrientation * orientation = nullptr;
        VelocityBehaviour2D  * velocityBehaviour = nullptr;
        std::map<Key, glm::vec2> controls;
        float speed = 150;

        void updateVelocity() {
            const glm::vec2 & facingDir = orientation->getFacingDirection();

            if (glm::length(facingDir) > 0) {
                velocityBehaviour->velocity = speed * glm::normalize(facingDir);
            } else {
                velocityBehaviour->velocity = {0, 0};
            }
        }

        void onKeyPressed(KeyPressedEvent& e) {
            if (e.repeated) return;

            auto i = controls.find(e.button);
            if (i != controls.end()) {
                orientation->setFacingDirection(orientation->getFacingDirection() + i->second);
                updateVelocity();
            }
        }

        void onKeyReleased(KeyReleasedEvent& e) {
            auto i = controls.find(e.button);
            if (i != controls.end()) {
                orientation->setFacingDirection(orientation->getFacingDirection() - i->second);
                updateVelocity();
            }
        }

    public:
        SimpleCharacterKeyboardControls() {
            controls = {
                    {Key::LEFT,  glm::vec2{-1,  0}},
                    {Key::RIGHT, glm::vec2{ 1,  0}},
                    {Key::UP,    glm::vec2{ 0,  1}},
                    {Key::DOWN,  glm::vec2{ 0, -1}}
            };
        }
        ~SimpleCharacterKeyboardControls() override = default;

        void attached(Entity &entity) override {
            Behaviour::attached(entity);
            EventService& e = Services::GetEventService();
            e.add<KeyPressedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyPressed>(this);
            e.add<KeyReleasedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyReleased>(this);

            velocityBehaviour = entity.get<VelocityBehaviour2D>();
            orientation = entity.get<CharacterOrientation>();
        }

        void detached(Entity &entity) override {
            Behaviour::detached(entity);
            EventService& e = Services::GetEventService();
            e.remove<KeyPressedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyPressed>(this);
            e.remove<KeyReleasedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyReleased>(this);

            velocityBehaviour = nullptr;
            orientation = nullptr;
        }
    };
}

#endif //PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H
