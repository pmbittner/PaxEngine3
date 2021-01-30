//
// Created by Paul Bittner on 30.01.2021.
//

#ifndef PAXENGINE3_ABILITY_H
#define PAXENGINE3_ABILITY_H

#include "../GameEntityProperty.h"
#include "AbilityIdentifier.h"

/**
 * Shorthand convenience macros for defining abilities.
 * It produces all mandatory annotations for a Property and introduces
 * a static field `Name` that holds the abilities name.
 */
#define PAX_ABILITY(name) \
    PAX_PROPERTY(name, PAX_PROPERTY_IS_CONCRETE) \
    PAX_PROPERTY_DERIVES(Ability) \
    PAX_PROPERTY_IS_SINGLE \
public: \
    static constexpr const char* GetName() { return #name; } \
private:

#define PAX_ABILITY_IMPL(...) PAX_PROPERTY_IMPL(__VA_ARGS__)

namespace PAX {
    class Ability : public GameEntityProperty {
        PAX_PROPERTY(Ability, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

    protected:
        explicit Ability(const AbilityIdentifier & name);

    public:
        const AbilityIdentifier name;
        virtual AbilityResult run() = 0;
    };
}

#endif //PAXENGINE3_ABILITY_H
