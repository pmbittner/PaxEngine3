//
// Created by Paul Bittner on 27.01.2021.
//

#ifndef MESHFOLD_PRIMITIVEFACTORY_H
#define MESHFOLD_PRIMITIVEFACTORY_H

#include "../data/Mesh.h"

namespace PAX {
    struct PrimitiveFactory {
        static std::shared_ptr<Mesh> CreateQuad(bool upload = true);
        static std::shared_ptr<Mesh> CreateFrame(bool upload = true);
        static std::shared_ptr<Mesh> CreateScreenQuad(float left, float right, float bottom, float top);
        static std::shared_ptr<Mesh> CreateScreenFillingQuad();
        static std::shared_ptr<Mesh> CreateCircle(int steps, bool upload = true);
        static std::shared_ptr<Mesh> CreateFilledCircle(int steps, bool upload = true);
    };
}

#endif //MESHFOLD_PRIMITIVEFACTORY_H
