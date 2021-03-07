//
// Created by Paul Bittner on 07.03.2021.
//

#ifndef PAXENGINE3_LETTER_H
#define PAXENGINE3_LETTER_H

#include "paxcore/rendering/graphics/SpriteSheetGraphics.h"

namespace PAX::Font {
    class Letter : public GameEntityProperty {
        PAX_PROPERTY(Letter, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(SpriteSheetGraphics)

        /// BEGIN FIELDS
        char character;
        /// END FIELDS

        Letter();

    public:
        PAX_IMPLICIT Letter(char character);

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_LETTER_H
