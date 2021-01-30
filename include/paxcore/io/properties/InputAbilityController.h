//
// Created by Paul Bittner on 30.01.2021.
//

#ifndef MESHFOLD_INPUTABILITYCONTROLLER_H
#define MESHFOLD_INPUTABILITYCONTROLLER_H

#include <map>

#include <paxcore/gameentity/property/Ability.h>
#include <paxcore/io/Keys.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/io/event/KeyReleasedEvent.h>

namespace PAX {
    class InputAbilityController : public GameEntityProperty {
        PAX_PROPERTY(InputAbilityController, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        std::map<Key, AbilityIdentifier> keyBindings;

    public:
        InputAbilityController();

        void bind(Key key, const AbilityIdentifier & ability);

        void spawned() override;
        void despawned() override;

        void onKeyPressed(KeyPressedEvent & e);
//        void onKeyReleased(KeyReleasedEvent & e);
    };
}

#endif //MESHFOLD_INPUTABILITYCONTROLLER_H
