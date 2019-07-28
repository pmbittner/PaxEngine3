//
// Created by Paul on 25.03.2018.
//

#ifndef PAXENGINE3_BOUNDINGBOX2D_H
#define PAXENGINE3_BOUNDINGBOX2D_H

#include <iostream>
#include <algorithm>

#include "Functions.h"
#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    template<typename Type, int dimensions>
    struct BoundingBox {
        using Vec = glm::vec<dimensions, Type, glm::defaultp>;

        Vec from;
        Vec to;

        BoundingBox(const Vec & from, const Vec & to) {
            BoundingBox::from = from;
            BoundingBox::to = to;
        }

        explicit BoundingBox(const Vec & length) {
            BoundingBox::from = -length / Type(2);
            BoundingBox::to   = +length / Type(2);
        }

        BoundingBox() {
            for (int i = 0; i < dimensions; ++i) {
                from[i] = 0;
                to[i]   = 0;
            }
        }

        Vec getCenter() const {
            return from + (to - from) / 2.f;
        }

        bool contains(const Vec & point) {
            // If the point lays outside in any dimension, return false.
            for (int i = 0; i < dimensions; ++i) {
                if (point[i] < from[i] || to[i] < point[i])
                    return false;
            }
            return true;
        }

        void operator +=(const BoundingBox<Type, dimensions> &box) {
            for (int i = 0; i < dimensions; ++i) {
                from[i] = (std::min)(from[i], box.from[i]);
                to[i] = (std::max)(to[i], box.to[i]);
            }
        }

        BoundingBox<Type, dimensions> operator +(const BoundingBox<Type, dimensions> &box) const {
            BoundingBox<Type, dimensions> copy = *this;
            copy += box;
            return copy;
        }

        void translate(const Vec & point) {
            from += point;
            to += point;
        }

        Type getLength(int i) const {
            return to[i] - from[i];
        }

        void print() const {
            std::cout << "[";
            for (int i = 0; i < dimensions; ++i) {
                std::cout << "\t[" << from[i] << ", " << to[i] << "]" << std::endl;
            }
            std::cout  << "]" << std::endl;
        }
    };

    typedef BoundingBox<int, 2> IntBoundingBox2D;
    typedef BoundingBox<float, 2> FloatBoundingBox2D;
    typedef BoundingBox<int, 3> IntBoundingBox3D;
    typedef BoundingBox<float, 3> FloatBoundingBox3D;
}
#endif //PAXENGINE3_BOUNDINGBOX2D_H
