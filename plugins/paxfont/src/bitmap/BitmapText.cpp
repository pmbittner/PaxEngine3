//
// Created by Paul Bittner on 07.03.2021.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include "paxfont/bitmap/BitmapText.h"

namespace PAX::Font {
    PAX_PROPERTY_IMPL(BitmapText)

    BitmapText::BitmapText() = default;

    BitmapText::BitmapText(const std::string &text, const std::shared_ptr<BitmapFont> &font, float fontsize) :
    SpriteGraphics(font->getBitmap()),
    text(text),
    font(font),
    fontsize(fontsize)
    {
        initBitmapText();
    }

    void BitmapText::initBitmapText() {
        textBlock.lines.push_back(TextLine::fromString(text));
        setMesh(font->bakeText(textBlock));
    }

    glm::vec3 BitmapText::computeScaling(const glm::vec3 &spriteSize) const {
        return glm::vec3(fontsize);
    }

    void BitmapText::created() {
        Super::created();
        initBitmapText();
    }

    ClassMetadata BitmapText::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(text)).addFlag(Field::IsMandatory);
        m.add(paxfieldof(font)).addFlag(Field::IsMandatory).addFlag(EngineFieldFlags::IsResource);
        m.add(paxfieldof(fontsize)).addFlag(Field::IsMandatory);
        return m;
    }
}