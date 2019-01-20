//
// Created by paul on 07.01.19.
//

#include "platformerdemo/behaviour/PlayerControls.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::PlayerControls, PAX_PROPERTY_IS_CONCRETE)

    PlayerControls * PlayerControls::createFromProvider(ContentProvider & provider) {
        return new PlayerControls();
    }

    void PlayerControls::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}