//
// Created by Paul Bittner on 28.03.2020.
//

#ifndef PAXENGINE3_PORTALGENERATOR_H
#define PAXENGINE3_PORTALGENERATOR_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/rendering/data/Mesh.h>
#include "Portal.h"

namespace PAX {
    class PortalGenerator {
        std::vector<glm::ivec3> faces;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;

        PAX_NODISCARD bool areVerticesEqual(int v0, int v1) const;
        PAX_NODISCARD bool areUVsEqual(int uv0, int uv1) const;

    public:
        explicit PortalGenerator(Mesh* mesh);
        PAX_NODISCARD std::vector<Portal> computePortals(const glm::mat3 & trafo) const;
    };
}
#endif //PAXENGINE3_PORTALGENERATOR_H
