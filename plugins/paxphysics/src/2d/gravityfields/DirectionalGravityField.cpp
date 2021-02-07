//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxphysics/2d/gravityfields/DirectionalGravityField.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(DirectionalGravityField)

    DirectionalGravityField::DirectionalGravityField() : GravityField() {}

    DirectionalGravityField::DirectionalGravityField(const std::shared_ptr<Shape2D> &shape,
                                                     float intensity,
                                                     const glm::vec2 &direction)
                                                     : GravityField(shape, intensity),
                                                     direction(glm::normalize(direction)) {}

    ClassMetadata DirectionalGravityField::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(direction)).addFlag(Field::IsMandatory);
        return m;
    }

    void DirectionalGravityField::created() {
        Super::created();
        // normalizing
        setDirection(getDirection());
    }

    glm::vec2 DirectionalGravityField::getFallingDirection(const glm::vec2 &point) const {
        GameEntity * owner = getOwner();
        if (owner) {
            return owner->getTransformation().getRotationAsMatrix() * glm::vec3(direction, 0);
        }
        return direction;
    }

    void DirectionalGravityField::setDirection(const glm::vec2 & direction) {
        this->direction = glm::normalize(direction);
    }

    const glm::vec2 & DirectionalGravityField::getDirection() const {
        return direction;
    }
}