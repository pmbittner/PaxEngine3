//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_FIXTURE2D_H
#define PAXENGINE3_FIXTURE2D_H

#include <memory>
#include <paxphysics/2d/shape/Shape2D.h>
#include <polypropylene/serialisation/json/JsonParser.h>
#include "paxphysics/2d/material/PhysicsMaterial.h"

namespace PAX {
    namespace Physics {
        class Fixture2D {
        public:
            std::shared_ptr<Shape2D> shape;
            std::shared_ptr<PhysicsMaterial> material;

            /// \param shape Takes ownership
            Fixture2D(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material);
            ~Fixture2D();
        };
    }
}

#endif //PAXENGINE3_FIXTURE2D_H
