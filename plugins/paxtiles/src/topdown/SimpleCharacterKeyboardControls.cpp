//
// Created by Paul on 21.05.2019.
//

#include <paxtiles/topdown/SimpleCharacterKeyboardControls.h>

namespace PAX::Tiles {
    PAX_PROPERTY_INIT(SimpleCharacterKeyboardControls) {

    }

    ClassMetadata SimpleCharacterKeyboardControls::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(speed));
        return m;
    }

    SimpleCharacterKeyboardControls::SimpleCharacterKeyboardControls() {
        controls = {
                {Key::LEFT,  glm::vec2{-1,  0}},
                {Key::RIGHT, glm::vec2{ 1,  0}},
                {Key::UP,    glm::vec2{ 0,  1}},
                {Key::DOWN,  glm::vec2{ 0, -1}}
        };
    }

    void SimpleCharacterKeyboardControls::updateVelocity() {
        const glm::vec2 & facingDir = orientation->getFacingDirection();

        if (glm::length(facingDir) > 0) {
            velocityBehaviour->velocity = speed * glm::normalize(facingDir);
        } else {
            velocityBehaviour->velocity = {0, 0};
        }
    }

    void SimpleCharacterKeyboardControls::onKeyPressed(PAX::KeyPressedEvent &e) {
        if (e.repeated) return;

        auto i = controls.find(e.button);
        if (i != controls.end()) {
            orientation->setFacingDirection(orientation->getFacingDirection() + i->second);
            updateVelocity();
        }
    }

    void SimpleCharacterKeyboardControls::onKeyReleased(PAX::KeyReleasedEvent &e) {
        auto i = controls.find(e.button);
        if (i != controls.end()) {
            orientation->setFacingDirection(orientation->getFacingDirection() - i->second);
            updateVelocity();
        }
    }

    void SimpleCharacterKeyboardControls::attached(PAX::GameEntity & e) {
        Super::attached(e);

        velocityBehaviour = e.get<VelocityBehaviour2D>();
        orientation = e.get<CharacterOrientation>();
    }

    void SimpleCharacterKeyboardControls::detached(PAX::GameEntity & e) {
        Super::detached(e);

        velocityBehaviour = nullptr;
        orientation = nullptr;
    }

    void SimpleCharacterKeyboardControls::spawned() {
        Super::spawned();
        EventService& e = Services::GetEventService();
        e.add<KeyPressedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyPressed>(this);
        e.add<KeyReleasedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyReleased>(this);
    }

    void SimpleCharacterKeyboardControls::despawned() {
        Super::despawned();
        EventService& e = Services::GetEventService();
        e.remove<KeyPressedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyPressed>(this);
        e.remove<KeyReleasedEvent, SimpleCharacterKeyboardControls, &SimpleCharacterKeyboardControls::onKeyReleased>(this);
    }

    void SimpleCharacterKeyboardControls::update(PAX::UpdateOptions &options) {}
}