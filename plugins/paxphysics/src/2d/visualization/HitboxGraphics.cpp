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

    std::shared_ptr<Mesh> HitboxGraphics::GetRectangleMesh() {
        static auto mesh = PrimitiveFactory::CreateQuad();
        return mesh;
    }

    std::shared_ptr<Mesh> HitboxGraphics::GetRectangleBorderMesh() {
        static auto mesh = PrimitiveFactory::CreateFrame();
        return mesh;
    }

    const glm::vec4 & HitboxGraphics::GetFillColorFor(Fixture2D &fixture) {
        static glm::vec4 color = glm::vec4(0, 1, 0, 0.3f);
        return color;
    }

    const glm::vec4 & HitboxGraphics::GetBorderColorFor(Fixture2D &fixture) {
        static glm::vec4 color = glm::vec4(0, 1, 0, 1);
        return color;
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

    HitboxGraphics::HitboxGraphics(Fixture2D &fixture)
    : fixture(fixture),
    fillColor(GetFillColorFor(fixture)),
    borderColor(GetBorderColorFor(fixture))
    {
        initShaders();

        std::shared_ptr<Mesh> shapeMesh;
        std::shared_ptr<Mesh> frameMesh;
        if (auto * rect = dynamic_cast<Rectangle*>(fixture.shape.get())) {
            shapeMesh = GetRectangleMesh();
            frameMesh = GetRectangleBorderMesh();
            const FloatBoundingBox2D & aabb = rect->getAABB();
            trafo = glm::scale(glm::vec3(
                            aabb.getLength(0),
                            aabb.getLength(1),
                            1));
            _shader = rectangleShader;
        } else {
            PAX_NOT_IMPLEMENTED_EXCEPTION();
        }

        shape = MeshNode(shapeMesh);
        frame = MeshNode(frameMesh);
    }

    void HitboxGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);

        const std::shared_ptr<Shader> shader = getShader();
        const glm::mat4 & parentTransform = renderOptions.getTransformationMatrix();
        renderOptions.setTransformationMatrix(parentTransform * trafo);

        shader->setUniform("color", fillColor);
        shape.render(renderOptions);

        shader->setUniform("color", borderColor);
        frame.render(renderOptions);

        renderOptions.setTransformationMatrix(parentTransform);
    }
}