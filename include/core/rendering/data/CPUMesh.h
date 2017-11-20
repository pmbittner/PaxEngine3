//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_CPUMESH_H
#define PAXENGINE3_CPUMESH_H

#include <glm/vec3.hpp>
#include <vector>

namespace PAX {
    struct CPUMesh {
        std::vector<glm::vec3> vertices;
        std::vector<glm::ivec3> faces;
    };
}

#endif //PAXENGINE3_CPUMESH_H
