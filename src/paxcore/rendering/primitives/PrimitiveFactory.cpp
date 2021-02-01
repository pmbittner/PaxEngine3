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

            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, indices);
            mesh->setFaceMode(Mesh::FaceMode::Triangles);
            mesh->addAttribute(Mesh::UVs, texCoords);

            if (upload) {
                mesh->upload();
            }
            return mesh;
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
        }
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateFrame(bool upload) {
        auto* meshFactory = Services::GetFactoryService().get<MeshFactory>();

        if (meshFactory) {
            std::vector<glm::vec3> vertices = {
                    {-0.5f, 0.5f,  0},  // V0
                    {-0.5f, -0.5f, 0},  // V1
                    {0.5f,  -0.5f, 0},  // V2
                    {0.5f,  0.5f,  0}   // V3
            };

            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, {});
            mesh->setFaceMode(Mesh::FaceMode::Lines);

            if (upload) {
                mesh->upload();
            }
            return mesh;
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
        }
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateScreenQuad(float left, float right, float bottom, float top) {
        std::vector<glm::vec3> vertices = {
                {left,  bottom, 0.f},
                {right, bottom, 0.f},
                {right, top,    0.f},
                {left,  top,    0.f}
        };

        std::vector<glm::vec2> uvs = {
                {0, 0},
                {1, 0},
                {1, 1},
                {0, 1}
        };

        std::vector<glm::ivec3> faces = {
                {0,1,2},
                {0,2,3}
        };

        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        PAX_ASSERT_NOT_NULL(meshFactory, "MeshFactory is required, but is not registered!");
        std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);
        mesh->addAttribute(Mesh::UVs, uvs);
        return mesh;
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateScreenFillingQuad() {
        return CreateScreenQuad(-1, 1, -1, 1);
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateCircle(int steps, bool upload) {
        auto* meshFactory = Services::GetFactoryService().get<MeshFactory>();

        if (meshFactory) {
            std::vector<glm::vec3> vertices(steps);
            for (int i = 0; i < steps; ++i) {
                const float rad = float(i) / float(steps) * glm::two_pi<float>();
                vertices[i] = {glm::sin(rad), glm::cos(rad), 0};
            }

            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, {});
            mesh->setFaceMode(Mesh::FaceMode::Lines);

            if (upload) {
                mesh->upload();
            }
            return mesh;
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
        }
    }

    std::shared_ptr<Mesh> PrimitiveFactory::CreateFilledCircle(int steps, bool upload) {
        auto* meshFactory = Services::GetFactoryService().get<MeshFactory>();

        if (meshFactory) {
            // +1 for the center of the circle
            const int center = steps;
            std::vector<glm::vec3> vertices(steps + 1);
            std::vector<glm::ivec3> faces(steps);
            vertices[center] = {0, 0, 0};
            for (int i = 1; i < steps + 1; ++i) {
                const float rad = float(i) / float(steps) * glm::two_pi<float>();
                vertices[i] = {glm::sin(rad), glm::cos(rad), 0};
                faces[i-1] = {i, center, (i+1) % steps};
            }

            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);
            mesh->setFaceMode(Mesh::FaceMode::Triangles);

            if (upload) {
                mesh->upload();
            }
            return mesh;
        } else {
            PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
        }
    }
}
