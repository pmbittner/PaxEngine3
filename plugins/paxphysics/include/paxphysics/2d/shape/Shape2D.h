//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_SHAPE2D_H
#define PAXENGINE3_SHAPE2D_H

#include <paxutil/math/BoundingBox.h>
#include <paxutil/event/EventHandler.h>
#include <paxutil/StringUtils.h>

namespace PAX::Physics {
    class Shape2D {
        bool synchroniseToSize = false;

    protected:
        FloatBoundingBox2D aabb;

    public:
        EventHandler<> ShapeChanged;

        Shape2D();
        Shape2D(const Shape2D & other);
        virtual ~Shape2D() = 0;

        [[nodiscard]] const FloatBoundingBox2D &getAABB() const;
        [[nodiscard]] bool synchronisesToSize() const;
        void setSynchroniseToSize(bool synchroniseToSize);
    };
}

#endif //PAXENGINE3_SHAPE2D_H