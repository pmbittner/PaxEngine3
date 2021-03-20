//
// Created by Paul Bittner on 07.03.2021.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include "paxfont/bitmap/BitmapText.h"

namespace PAX::Font {
    PAX_PROPERTY_IMPL(BitmapText)

    BitmapText::BitmapText() = default;

    BitmapText::BitmapText(const TextBlock &text, const std::shared_ptr<BitmapFont> &font, float fontsize) :
    SpriteGraphics(font->getBitmap()),
    text(text),
    font(font),
    fontsize(fontsize)
    {
        updateText();
    }

    void BitmapText::updateText() {
        setMesh(font->bakeText(text, size));
    }

    glm::vec2 BitmapText::getSpriteSize() const {
        return fontsize * size;
    }

    void BitmapText::created() {
        Super::created();
        updateText();
    }

    ClassMetadata BitmapText::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(text)).addFlag(Field::IsMandatory);
        m.add(paxfieldof(font)).addFlag(Field::IsMandatory).addFlag(EngineFieldFlags::IsResource);
        m.add(paxfieldof(fontsize)).addFlag(Field::IsMandatory);
        return m;
    }

    const TextBlock & BitmapText::getText() const {
        return text;
    }

    void BitmapText::setText(const TextBlock &t) {
        text = t;
        // very naive and expensive
        updateText();
        updateSizeProperty();
    }
}