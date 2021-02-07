//
// Created by Paul Bittner on 23.01.2021.
//

#include <paxphysics/2d/gravityfields/SphereGravityField.h>
#include <paxphysics/2d/shape/Circle.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(SphereGravityField)

    SphereGravityField::SphereGravityField() : GravityField() {}

    SphereGravityField::SphereGravityField(float intensity, float radius, const glm::vec2 &offset)
    : SphereGravityField(std::make_shared<Circle>(radius), intensity, radius, offset) {}

    SphereGravityField::SphereGravityField(
            const std::shared_ptr<Shape2D> & shape, float intensity, float radius, const glm::vec2 & offset)
    : GravityField(shape, intensity), radius(radius), offset(offset) {}

    ClassMetadata SphereGravityField::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(radius)).addFlag(Field::IsMandatory);
        m.add(paxfieldof(offset)).addFlag(Field::IsMandatory);
        return m;
    }

    glm::vec2 SphereGravityField::getFallingDirection(const glm::vec2 &point) const {
        const GameEntity * e = getOwner();
        if (e) {
            return e->getTransformation().position2D() + offset - point;
        }
        return glm::vec2(0);
    }

    void SphereGravityField::setRadius(float radius) {
        this->radius = radius;
    }

    float SphereGravityField::getRadius() const {
        return radius;
    }
}