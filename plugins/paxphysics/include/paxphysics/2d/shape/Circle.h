//
// Created by Paul Bittner on 01.02.2021.
//

#ifndef MESHFOLD_CIRCLE_H
#define MESHFOLD_CIRCLE_H

#include "Shape2D.h"

namespace PAX::Physics {
    class Circle : public Shape2D {
        float radius = 1;

    public:
        explicit Circle(float radius);
        ~Circle() override;

        float getRadius() const;
    };
}

#endif //MESHFOLD_CIRCLE_H
