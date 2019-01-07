//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_MESHFACTORY_H
#define PAXENGINE3_MESHFACTORY_H

#include <paxcore/rendering/data/Mesh.h>

namespace PAX {
    class MeshFactory {
    public:
        virtual std::shared_ptr<Mesh> create(const std::vector<glm::vec3> & vertices, const std::vector<glm::ivec3> & faces) = 0;
    };
}

#endif //PAXENGINE3_MESHFACTORY_H
