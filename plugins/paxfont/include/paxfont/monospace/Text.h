//
// Created by Paul Bittner on 07.03.2021.
//

#ifndef PAXENGINE3_TEXT_H
#define PAXENGINE3_TEXT_H

#include "paxcore/gameentity/GameEntityProperty.h"
#include "Letter.h"

namespace PAX::Font {
    class Text : public GameEntityProperty {
        PAX_PROPERTY(Text, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        std::shared_ptr<GameEntityPrefab> letterPrefab;
        std::vector<Letter*> letters;

        std::string text;
    };
}

#endif //PAXENGINE3_TEXT_H
