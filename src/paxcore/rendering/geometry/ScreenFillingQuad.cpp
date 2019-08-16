//
// Created by Bittner on 16/08/2019.
//

#include <paxcore/rendering/geometry/ScreenFillingQuad.h>
#include <paxcore/service/Services.h>

namespace PAX {
    std::shared_ptr<Mesh> CreateScreenQuad(float left, float right, float bottom, float top) {
        std::vector<glm::vec3> vertices = {
                {left,  bottom, 0.f},
                {right, bottom, 0.f},
                {right, top,    0.f},
                {left,  top,    0.f}
        };

        std::vector<glm::ivec3> faces = {
                {0,1,2},
                {0,2,3}
        };

        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        PAX_ASSERT_NOT_NULL(meshFactory, "MeshFactory is required, but is not registered!");
        std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);
        return mesh;
    }

    std::shared_ptr<Mesh> CreateScreenFillingQuad() {
        return CreateScreenQuad(-1, 1, -1, 1);
    }
}