//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_GRAVITYFIELDSENSITIVE_H
#define MESHFOLD_GRAVITYFIELDSENSITIVE_H

#include "paxcore/gameentity/GameEntityProperty.h"

namespace PAX::Physics {
    class GravityFieldSensitive : public GameEntityProperty {
        PAX_PROPERTY(GravityFieldSensitive, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE
    };
}

#endif //MESHFOLD_GRAVITYFIELDSENSITIVE_H
