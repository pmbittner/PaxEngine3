//
// Created by Paul Bittner on 30.01.2021.
//

#ifndef PAXENGINE3_ABILITY_H
#define PAXENGINE3_ABILITY_H

#include "Behaviour.h"
#include "AbilityIdentifier.h"

/**
 * Shorthand convenience macros for defining abilities.
 * It produces all mandatory annotations for a Property and introduces
 * a static field `Name` that holds the abilities name.
 */
#define PAX_ABILITY(name) \
    PAX_PROPERTY(name, PAX_PROPERTY_IS_CONCRETE) \
    PAX_PROPERTY_DERIVES(Ability) \
public: \
    static constexpr const char* GetName() { return #name; } \
private:

#define PAX_ABILITY_IMPL(...) PAX_PROPERTY_IMPL(__VA_ARGS__)

namespace PAX {
    class Ability : public Behaviour {
        PAX_PROPERTY(Ability, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Behaviour)
        PAX_PROPERTY_IS_MULTIPLE

    protected:
        bool isActive;
        AbilityIdentifier name;
        explicit Ability(const AbilityIdentifier & name);

    public:
        void update(UpdateOptions & options) final;

        virtual AbilityResult start();
        virtual void act(UpdateOptions & options);
        virtual AbilityResult stop();

        PAX_NODISCARD const AbilityIdentifier & getName();
    };
}

#endif //PAXENGINE3_ABILITY_H
