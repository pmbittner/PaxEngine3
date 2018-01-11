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

    void SpriteSheetGraphics::initializeTransformation() {
        glm::ivec2 size = getSpriteSheetSize();
        _trafoNode.setTransformation(
                glm::scale(
                        glm::mat4(1),
                        glm::vec3(
                                _texture->getWidth() / size.x,
                                _texture->getHeight() / size.y,
                                1
                        )
                )
        );
    }

    void SpriteSheetGraphics::registerFlags(Shader::Flags &flags) {
        _spriteSheet.registerFlags(flags);
        SpriteGraphics::registerFlags(flags);
    }

    void SpriteSheetGraphics::setSpritePosition(int x, int y) {
        _spriteSheet.setOffset(x, y);
    }

    glm::ivec2 SpriteSheetGraphics::getSpritePosition() {
        return _spriteSheet.getOffset();
    }

    glm::ivec2 SpriteSheetGraphics::getSpriteSheetSize() {
        return _spriteSheet.getSize();
    }

    void SpriteSheetGraphics::setShader(std::shared_ptr<Shader> &shader) {
        _spriteSheet.cacheUniformsFor(shader);
        SpriteGraphics::setShader(shader);
    }
}