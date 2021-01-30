//
// Created by Paul Bittner on 30.01.2021.
//

#include <paxcore/io/properties/InputAbilityController.h>
#include <paxcore/service/Services.h>

namespace PAX {
    PAX_PROPERTY_IMPL(InputAbilityController)

    InputAbilityController::InputAbilityController() = default;

    void InputAbilityController::bind(Key key, const AbilityIdentifier & ability) {
        keyBindings[key] = ability;
    }

    void InputAbilityController::spawned() {
        EventService & events = Services::GetEventService();
        events.add<KeyPressedEvent,  InputAbilityController, &InputAbilityController::onKeyPressed>(this);
//        events.add<KeyReleasedEvent, InputAbilityController, &InputAbilityController::onKeyReleased>(this);
    }

    void InputAbilityController::despawned() {
        EventService & events = Services::GetEventService();
        events.remove<KeyPressedEvent, InputAbilityController, &InputAbilityController::onKeyPressed>(this);
//        events.remove<KeyReleasedEvent, InputAbilityController, &InputAbilityController::onKeyReleased>(this);
    }

    void InputAbilityController::onKeyPressed(KeyPressedEvent & e) {
        if (!e.repeated) {
            const auto binding = keyBindings.find(e.button);
            if (binding != keyBindings.end()) {
                getOwner()->perform(binding->second);
            }
        }
    }

//    void InputAbilityController::onKeyReleased(KeyReleasedEvent & e) {
//
//    }
}