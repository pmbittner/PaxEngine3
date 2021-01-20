//
// Created by Paul on 09.01.2018.
//

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::SpriteSheetGraphics)

    void SpriteSheetGraphics::init() {
        setSpritePosition(startPos);
        _spriteSheet.setSize({columns, rows});

        // put the spritesheet node in between the scenegraph root and the rest
        auto children = _scenegraph.getChildren();

        for (auto child : children) {
            _scenegraph.removeChild(child);
            _spriteSheet.addChild(child);
        }

        _scenegraph <<= _spriteSheet;
    }

    SpriteSheetGraphics::SpriteSheetGraphics() : _spriteSheet(0, 0) {

    }

    void SpriteSheetGraphics::created() {
        Super::created();
        init();
    }

    ClassMetadata SpriteSheetGraphics::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(columns)).flags |= Field::IsMandatory;
        m.add(paxfieldof(rows)).flags |= Field::IsMandatory;
        m.add(paxfieldalias("position", startPos));
        return m;
    }

    SpriteSheetGraphics::SpriteSheetGraphics(const std::shared_ptr<Texture> &texture, int columns, int rows) :
            SpriteGraphics(texture),
            _spriteSheet(columns, rows)
    {
        init();
    }

    glm::vec2 SpriteSheetGraphics::getSpriteSize() const {
        glm::ivec2 size = getSpriteSheetSize();
        return glm::vec2(_texture->getWidth() / size.x, _texture->getHeight() / size.y);
    }

    void SpriteSheetGraphics::setSpritePosition(int x, int y) {
        _spriteSheet.setOffset(x, y);
    }

    void SpriteSheetGraphics::setSpritePosition(const glm::ivec2 & pos) {
        setSpritePosition(pos.x, pos.y);
    }

    const glm::ivec2 & SpriteSheetGraphics::getSpritePosition() const {
        return _spriteSheet.getOffset();
    }

    const glm::ivec2 & SpriteSheetGraphics::getSpriteSheetSize() const {
        return _spriteSheet.getSize();
    }
}