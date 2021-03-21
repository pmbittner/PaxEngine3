//
// Created by Paul Bittner on 14.03.2021.
//

#ifndef PAXENGINE3_BITMAPFONT_H
#define PAXENGINE3_BITMAPFONT_H

#include "paxutil/lib/GlmIncludes.h"
#include "paxcore/rendering/data/Texture.h"
#include "paxcore/rendering/data/Mesh.h"
#include "polypropylene/serialisation/json/JsonTypeConverter.h"

namespace PAX::Font {
    // Looks bad but simple for now + for utf8 + for emojis
    using Character = std::string;

    struct CharacterInfo {
        int width;
        glm::ivec2 textLineOffset;
        glm::ivec2 pos;
        glm::ivec2 size;
        Character key;
    };

    struct TextLine {
        std::vector<Character> chars;
        static TextLine fromString(const std::string & s);
        PAX_NODISCARD std::string toString() const;
    };

    struct TextBlock {
        std::vector<TextLine> lines;
    };

    struct FontMetadata {
        int size;
        std::string family;
        int height;
        std::string style;
    };

    class BitmapFont {
        std::shared_ptr<Texture> bitmap;
        std::map<Character, CharacterInfo> characters;

        FontMetadata metadata;

        glm::vec2 toUV(const glm::vec2 & pixelCoordinates);

    public:
        BitmapFont(
                const FontMetadata & metadata,
                const std::shared_ptr<Texture> & bitmap,
                const std::vector<CharacterInfo> & charInfo);

        PAX_NODISCARD std::shared_ptr<Mesh> bakeText(const TextBlock & text, glm::vec2 & outMeshSize);
        PAX_NODISCARD const std::shared_ptr<Texture> & getBitmap() const;
    };
}

PAX_DECLARE_JSON_CONVERTER_FOR(Font::TextLine)
PAX_DECLARE_JSON_CONVERTER_FOR(Font::TextBlock)
std::ostream & operator<<(std::ostream & str, const PAX::Font::TextLine & l);
std::ostream & operator<<(std::ostream & str, const PAX::Font::TextBlock & b);

#endif //PAXENGINE3_BITMAPFONT_H
