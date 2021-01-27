//
// Created by Paul Bittner on 27.01.2021.
//

#include <paxphysics/2d/visualization/HitboxGraphics.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <paxcore/rendering/primitives/PrimitiveFactory.h>
#include <paxcore/service/Services.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(HitboxGraphics)

    std::shared_ptr<Shader> HitboxGraphics::rectangleShader;

    ClassMetadata HitboxGraphics::getMetadata() {
        PAX_THROW_RUNTIME_ERROR("Not supported.");
    }

    void HitboxGraphics::initShaders() {
        if (!rectangleShader) {
            rectangleShader = Services::GetResources().loadOrGet<Shader>(
                    Shader::FileInfo(
                            Services::GetPaths().getEngineResourceDirectory() + "/shader/hitbox/rect.vert",
                            Services::GetPaths().getEngineResourceDirectory() + "/shader/hitbox/rect.frag"
                    ));
        }
    }

    HitboxGraphics::HitboxGraphics(Fixture2D &fixture) : fixture(fixture) {
        initShaders();

        std::shared_ptr<Mesh> mesh;
        if (auto * rect = dynamic_cast<Rectangle*>(fixture.shape.get())) {
            mesh = PrimitiveFactory::CreateQuad();
            const FloatBoundingBox2D & aabb = rect->getAABB();
            trafoNode.setTransformation(
                    glm::scale(glm::vec3(
                            aabb.getLength(0),
                            aabb.getLength(1),
                            1)));
            _shader = rectangleShader;
        } else {
            PAX_NOT_IMPLEMENTED_EXCEPTION();
        }

        meshNode = MeshNode(mesh);
        trafoNode <<= meshNode;
    }

    void HitboxGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);

        const std::shared_ptr<Shader> shader = getShader();
        shader->setUniform("color", glm::vec4(0, 1, 0, 0.3f));
        meshNode.getMesh()->setFaceMode(Mesh::FaceMode::Triangles);
        trafoNode.render(renderOptions);
        shader->setUniform("color", glm::vec4(0, 1, 0, 1));
        meshNode.getMesh()->setFaceMode(Mesh::FaceMode::Lines);
        trafoNode.render(renderOptions);
    }
}