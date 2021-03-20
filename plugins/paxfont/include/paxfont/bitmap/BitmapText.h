//
// Created by Paul Bittner on 07.03.2021.
//

#ifndef PAXENGINE3_BITMAPTEXT_H
#define PAXENGINE3_BITMAPTEXT_H

#include "paxcore/rendering/graphics/SpriteGraphics.h"
#include "BitmapFont.h"

namespace PAX::Font {
    class BitmapText : public SpriteGraphics {
        PAX_PROPERTY(BitmapText, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(SpriteGraphics)
        PAX_PROPERTY_IS_SINGLE

        TextBlock textBlock;
        /// BEGIN FIELDS
        std::string text;
        std::shared_ptr<BitmapFont> font;
        float fontsize = 1;
        /// END FIELDS

        glm::vec2 size;

        BitmapText();
        void initBitmapText();

    public:
        explicit BitmapText(const std::string & text, const std::shared_ptr<BitmapFont> & font, float fontsize);

        void created() override;
        PAX_NODISCARD glm::vec2 getSpriteSize() const override;
        PAX_NODISCARD ClassMetadata getMetadata() override;

        PAX_NODISCARD const TextBlock & getText() const;
       void setText(const TextBlock & t);
    };
}

#endif //PAXENGINE3_BITMAPTEXT_H
