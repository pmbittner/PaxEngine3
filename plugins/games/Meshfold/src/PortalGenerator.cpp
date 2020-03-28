//
// Created by Paul Bittner on 28.03.2020.
//

#include "meshfold/PortalGenerator.h"

namespace PAX {
    PortalGenerator::PortalGenerator(PAX::Mesh *mesh) {
        mesh->getFaces(faces);
        mesh->getAttribute(Mesh::UVs, uvs);
        mesh->getAttribute(Mesh::Vertices, vertices);
    }

    bool PortalGenerator::areVerticesEqual(int v0, int v1) const {
        return v0 == v1 || vertices.at(v0) == vertices.at(v1);
    }

    bool PortalGenerator::areUVsEqual(int uv0, int uv1) const {
        return uv0 == uv1 || uvs.at(uv0) == uvs.at(uv1);
    }

    std::vector<Portal> PortalGenerator::computePortals(const glm::vec2 &worldSize) const {
        std::vector<Portal> portals;

        for (size_t i = 0; i < faces.size(); ++i) {
            for (size_t j = i + 1; j < faces.size(); ++j) {
                const glm::ivec3 face0 = faces.at(i);
                const glm::ivec3 face1 = faces.at(j);

                for (int v0 = 0; v0 < 3; ++v0) {
                    for (int v1 = 0; v1 < 3; ++v1) {
                        int vertex0 = face0[v0];
                        int vertex1 = face1[v1];

                        int vertex0Next = face0[(v0 + 1) % 3];
                        int vertex1Prev = face1[(v1 + 2) % 3];

                        if (
                                areVerticesEqual(vertex0, vertex1)
                                && areVerticesEqual(vertex0Next, vertex1Prev))
                        {
                            // edge match
                            if (vertex0 != vertex1 || vertex0Next != vertex1Prev) {
                                if (! (areUVsEqual(vertex0, vertex1) && areUVsEqual(vertex0Next, vertex1Prev))) {
                                    // We have detected an edge with a discontinuity in the uv space
                                    Portal p0(worldSize * uvs.at(vertex0), worldSize * uvs.at(vertex0Next));
                                    Portal p1(worldSize * uvs.at(vertex1), worldSize * uvs.at(vertex1Prev));
                                    portals.push_back(p0);
                                    portals.push_back(p1);

                                    const size_t p0Index = portals.size() - 2;
                                    const size_t p1Index = portals.size() - 1;
                                    portals.at(p0Index).target = p1Index;
                                    portals.at(p1Index).target = p0Index;
                                }
                            }
                        }
                    }
                }
            }
        }

        return portals;
    }
}