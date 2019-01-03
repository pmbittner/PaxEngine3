//
// Created by paul on 03.01.19.
//

#include <paxcore/rendering/data/SpriteSheet.h>

namespace PAX {
    SpriteSheet::SpriteSheet(const std::shared_ptr <PAX::Texture> &texture, int columns, int rows) : texture(texture), dimensions(columns, rows) {

    }

    const std::shared_ptr<Texture> SpriteSheet::getTexture() {
        return texture;
    }

    glm::ivec2 SpriteSheet::getDimensions() {
        return dimensions;
    }

    glm::vec2 SpriteSheet::getScale() {
        return {
                texture->getWidth() / static_cast<float>(dimensions.x),
                texture->getHeight() / static_cast<float>(dimensions.y)};
    }
}