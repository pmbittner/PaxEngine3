//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/shape/Shape2D.h>

namespace PAX::Physics {
    Shape2D::Shape2D() : offset(0) {}

    Shape2D::Shape2D(const PAX::Physics::Shape2D &other) :
    aabb(other.aabb), synchroniseToSize(other.synchroniseToSize), offset(other.offset)
    {

    }

    Shape2D::~Shape2D() = default;

    const FloatBoundingBox2D &Shape2D::getAABB() const {
        return aabb;
    }

    bool Shape2D::synchronisesToSize() const {
        return synchroniseToSize;
    }

    void Shape2D::setSynchroniseToSize(bool synchroniseToSize) {
        this->synchroniseToSize = synchroniseToSize;
    }

    const glm::vec2 &Shape2D::getOffset() const {
        return offset;
    }

    void Shape2D::setOffset(const glm::vec2 &offset) {
        Shape2D::offset = offset;
    }
}