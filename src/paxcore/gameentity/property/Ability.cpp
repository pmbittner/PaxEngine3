//
// Created by Paul Bittner on 30.01.2021.
//

#include <paxcore/gameentity/property/Ability.h>

namespace PAX {
    PAX_PROPERTY_IMPL(Ability)

    Ability::Ability(const AbilityIdentifier & name) : name(name) {}
}