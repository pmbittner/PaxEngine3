//
// Created by Paul on 21.05.2019.
//

#include <paxtiles/topdown/CharacterOrientation.h>

namespace PAX::Tiles {
    PAX_PROPERTY_INIT(CharacterOrientation) {}

    CharacterOrientation::CharacterOrientation() : GameEntityProperty(), facingDirection(0, 0) {}

    CharacterOrientation::~CharacterOrientation() = default;

    void CharacterOrientation::setFacingDirection(const glm::vec2 & dir) {
        facingDirection = dir;
    }

    const glm::vec2 & CharacterOrientation::getFacingDirection() const {
        return facingDirection;
    }
}