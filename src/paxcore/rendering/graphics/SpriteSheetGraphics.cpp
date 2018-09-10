//
// Created by Paul on 09.01.2018.
//

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>

namespace PAX {
    SpriteSheetGraphics::SpriteSheetGraphics(const std::shared_ptr <Texture> &texture, int columns, int rows) :
            SpriteGraphics(texture),
            _spriteSheet(columns, rows)
    {
        // put the spritesheet node in between the scenegraph root and the rest
        auto children = _scenegraph.getChildren();

        for (auto child : children) {
            _scenegraph.removeChild(child);
            _spriteSheet.addChild(child);
        }

        _scenegraph <<= &_spriteSheet;
    }

    glm::vec2 SpriteSheetGraphics::getSpriteSize() const {
        glm::ivec2 size = getSpriteSheetSize();
        return glm::vec2(_texture->getWidth() / size.x, _texture->getHeight() / size.y);
    }

    void SpriteSheetGraphics::registerFlags(Shader::Flags &flags) {
        _spriteSheet.registerFlags(flags);
        SpriteGraphics::registerFlags(flags);
    }

    void SpriteSheetGraphics::setSpritePosition(int x, int y) {
        _spriteSheet.setOffset(x, y);
    }

    glm::ivec2 SpriteSheetGraphics::getSpritePosition() const {
        return _spriteSheet.getOffset();
    }

    glm::ivec2 SpriteSheetGraphics::getSpriteSheetSize() const {
        return _spriteSheet.getSize();
    }

    void SpriteSheetGraphics::setShader(std::shared_ptr<Shader> &shader) {
        _spriteSheet.cacheUniformsFor(shader);
        SpriteGraphics::setShader(shader);
    }
}