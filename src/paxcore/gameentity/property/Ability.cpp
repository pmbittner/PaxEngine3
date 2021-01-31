//
// Created by Paul Bittner on 30.01.2021.
//

#include <paxcore/gameentity/property/Ability.h>

namespace PAX {
    PAX_PROPERTY_IMPL(Ability)

    Ability::Ability(const AbilityIdentifier & name) : name(name) {}

    AbilityResult Ability::start() {
        isActive = true;
        return AbilityResult::Success;
    }

    void Ability::act(UpdateOptions &options) {}

    void Ability::update(UpdateOptions &options) {
        if (isActive) {
            act(options);
        }
    }

    AbilityResult Ability::stop() {
        isActive = false;
        return AbilityResult::Success;
    }

    const AbilityIdentifier & Ability::getName() {
        return name;
    }
}