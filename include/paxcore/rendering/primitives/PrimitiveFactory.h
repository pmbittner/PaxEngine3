//
// Created by Paul Bittner on 27.01.2021.
//

#ifndef MESHFOLD_PRIMITIVEFACTORY_H
#define MESHFOLD_PRIMITIVEFACTORY_H

#include "../data/Mesh.h"

namespace PAX {
    struct PrimitiveFactory {
        static std::shared_ptr<Mesh> CreateQuad(bool upload = true);
    };
}

#endif //MESHFOLD_PRIMITIVEFACTORY_H
