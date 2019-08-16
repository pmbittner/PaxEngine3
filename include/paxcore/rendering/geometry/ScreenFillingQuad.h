//
// Created by Bittner on 16/08/2019.
//

#ifndef PAXENGINE3_SCREENFILLINGQUAD_H
#define PAXENGINE3_SCREENFILLINGQUAD_H

#include "../factory/MeshFactory.h"

namespace PAX {
    std::shared_ptr<Mesh> CreateScreenQuad(float left, float right, float bottom, float top);
    std::shared_ptr<Mesh> CreateScreenFillingQuad();
}

#endif //PAXENGINE3_SCREENFILLINGQUAD_H
