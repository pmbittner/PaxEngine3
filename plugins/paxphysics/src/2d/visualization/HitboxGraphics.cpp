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

    const glm::vec4 & HitboxGraphics::GetFillColorFor(const Shape2D &fixture) {
        static glm::vec4 color = glm::vec4(0, 1, 0, 0.3f);
        return color;
    }

    const glm::vec4 & HitboxGraphics::GetBorderColorFor(const Shape2D &fixture) {
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

    HitboxGraphics::HitboxGraphics(const Shape2D & shape)
    :
    fillColor(GetFillColorFor(shape)),
    borderColor(GetBorderColorFor(shape))
    {
        initShaders();

        std::shared_ptr<Mesh> shapeMesh;
        std::shared_ptr<Mesh> frameMesh;
        if (const auto * rect = dynamic_cast<const Rectangle*>(&shape)) {
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

        shapeNode = MeshNode(shapeMesh);
        frameNode = MeshNode(frameMesh);
    }

    void HitboxGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);

        const std::shared_ptr<Shader> shader = getShader();
        const glm::mat4 & parentTransform = renderOptions.getTransformationMatrix();
        renderOptions.setTransformationMatrix(parentTransform * trafo);

        shader->setUniform("color", fillColor);
        shapeNode.render(renderOptions);

        shader->setUniform("color", borderColor);
        frameNode.render(renderOptions);

        renderOptions.setTransformationMatrix(parentTransform);
    }
}