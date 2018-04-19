//
// Created by Paul on 09.01.2018.
//

#include <core/rendering/graphics/SpriteSheetGraphics.h>
#include <glm/gtc/matrix_transform.hpp>

namespace PAX {
    SpriteSheetGraphics::SpriteSheetGraphics(const std::shared_ptr <Texture> &texture, int columns, int rows) :
            SpriteGraphics(texture),
            _spriteSheet(columns, rows)
    {
        _scenegraph <<= _trafoNode <<= _textureNode <<= _spriteSheet <<= &_meshNode;
    }

    const glm::vec2& SpriteSheetGraphics::getSpriteSize() const {
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