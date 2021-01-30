//
// Created by Paul on 21.05.2019.
//

#ifndef PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H
#define PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/gameentity/property/behaviours/2d/Movement2D.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/service/Services.h>

#include "CharacterOrientation.h"

namespace PAX::Tiles {
    class SimpleCharacterKeyboardControls : public Behaviour {
        PAX_PROPERTY(SimpleCharacterKeyboardControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(Movement2D, CharacterOrientation)

        CharacterOrientation * orientation = nullptr;
        Movement2D  * velocityBehaviour = nullptr;
        std::map<Key, glm::vec2> controls;
        float speed = 1;

        void updateVelocity();

        void onKeyPressed(KeyPressedEvent& e);
        void onKeyReleased(KeyReleasedEvent& e);

    public:
        SimpleCharacterKeyboardControls();
        ~SimpleCharacterKeyboardControls() override = default;

        void attached(GameEntity&) override;
        void detached(GameEntity&) override;

        void update(UpdateOptions & options) override;

        void spawned() override;
        void despawned() override;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_SIMPLECHARACTERKEYBOARDCONTROLS_H
