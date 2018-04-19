//
// Created by Paul on 25.03.2018.
//

#ifndef PAXENGINE3_BOUNDINGBOX2D_H
#define PAXENGINE3_BOUNDINGBOX2D_H

#include <iostream>
#include <algorithm>
#include "Functions.h"

namespace PAX {
    template<typename Type, int dimensions>
    struct BoundingBox {
        Type from[dimensions];
        Type to[dimensions];

        BoundingBox(const Type from[dimensions], const Type to[dimensions]) {
            for (int i = 0; i < dimensions; ++i) {
                BoundingBox::from[i] = from[i];
                BoundingBox::to[i] = to[i];
            }
        }

        BoundingBox() {
            for (int i = 0; i < dimensions; ++i) {
                from[i] = 0;
                to[i] = 0;
            }
        }

        bool contains(Type point[dimensions]) {
            for (int i = 0; i < dimensions; ++i) {
                if (point[i] < from[i] || to[i] < point[i])
                    return false;
            }
            return true;
        }

        BoundingBox<Type, dimensions> operator +(const BoundingBox<Type, dimensions> &box) {
            Type f[dimensions];
            Type t[dimensions];
            for (int i = 0; i < dimensions; ++i) {
                f[i] = (std::min)(from[i], box.from[i]);
                t[i] = (std::max)(to[i], box.to[i]);
            }
            return BoundingBox<Type, dimensions>(f, t);
        }

        void operator +=(const BoundingBox<Type, dimensions> &box) {
            for (int i = 0; i < dimensions; ++i) {
                from[i] = (std::min)(from[i], box.from[i]);
                to[i] = (std::max)(to[i], box.to[i]);
            }
        }

        Type getLength(int i) {
            return to[i] - from[i];
        }

        void print() {
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
