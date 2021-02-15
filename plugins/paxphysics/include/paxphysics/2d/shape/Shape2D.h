//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_SHAPE2D_H
#define PAXENGINE3_SHAPE2D_H

#include <paxutil/math/BoundingBox.h>
#include <polypropylene/event/EventHandler.h>
#include <polypropylene/stdutils/StringUtils.h>

namespace PAX::Physics {
    // TODO: This should actually be a sum type.
    //       So maybe we can implement it as such and avoid inheritance.
    class Shape2D {
        bool synchroniseToSize = false;

    protected:
        FloatBoundingBox2D aabb;
        glm::vec2 offset;

    public:
        EventHandler<> ShapeChanged;

        Shape2D();
        Shape2D(const Shape2D & other);
        virtual ~Shape2D() = 0;

        PAX_NODISCARD const FloatBoundingBox2D &getAABB() const;
        PAX_NODISCARD bool synchronisesToSize() const;
        void setSynchroniseToSize(bool synchroniseToSize);
        PAX_NODISCARD const glm::vec2 &getOffset() const;
        void setOffset(const glm::vec2 &offset);
    };
}

#endif //PAXENGINE3_SHAPE2D_H
