//
// Created by Paul Bittner on 27.01.2021.
//

#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include "paxcore/rendering/primitives/PrimitiveFactory.h"

namespace PAX {
    std::shared_ptr<Mesh> PrimitiveFactory::CreateQuad(bool upload) {
        auto* meshFactory = Services::GetFactoryService().get<MeshFactory>();

        if (meshFactory) {
            std::vector<glm::vec3> vertices = {
                    {-0.5f, 0.5f,  0},  // V0
                    {-0.5f, -0.5f, 0},  // V1
                    {0.5f,  -0.5f, 0},  // V2
                    {0.5f,  0.5f,  0}   // V3
            };

            std::vector<glm::ivec3> indices = {
                    {0, 1, 3},  // Top    left  triangle (V0,V1,V3)
                    {3, 1, 2}   // Bottom right triangle (V3,V1,V2)
            };

            std::vector<glm::vec2> texCoords = {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {1, 0}
            };

//                PAX_LOG(Log::Level::Info, "create QuadMesh");

            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, indices);
            mesh->addAttribute(Mesh::UVs, texCoords);

            if (upload) {
                mesh->upload();
            }
            return mesh;
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
        }
    }
}
