//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_RECTANGLE_H
#define PAXENGINE3_RECTANGLE_H

#include "Shape2D.h"

namespace PAX::Physics {
    class Rectangle : public Shape2D {
    public:
        explicit Rectangle(const glm::vec2 & size);
        ~Rectangle() override;
    };
}

#endif //PAXENGINE3_RECTANGLE_H
