//
// Created by Paul Bittner on 27.01.2021.
//

#include <paxphysics/2d/visualization/HitboxGraphics.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <paxcore/rendering/primitives/PrimitiveFactory.h>
#include <paxcore/service/Services.h>
#include <paxphysics/2d/shape/Circle.h>

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

    std::shared_ptr<Mesh> HitboxGraphics::GetCircleMesh() {
        static auto mesh = PrimitiveFactory::CreateFilledCircle(64); // about 10 * two pi
        return mesh;
    }

    std::shared_ptr<Mesh> HitboxGraphics::GetCircleBorderMesh() {
        static auto mesh = PrimitiveFactory::CreateCircle(64);
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
        } else if (const auto * circle = dynamic_cast<const Circle*>(&shape)) {
            shapeMesh = GetCircleMesh();
            frameMesh = GetCircleBorderMesh();
            trafo = glm::scale(glm::vec3(circle->getRadius(), circle->getRadius(), 1));
            _shader = rectangleShader;
        } else {
            PAX_NOT_IMPLEMENTED_EXCEPTION();
        }

        trafo = glm::translate(glm::vec3(shape.getOffset(), 0)) * trafo;

        shapeNode = MeshNode(shapeMesh);
        frameNode = MeshNode(frameMesh);
    }

    void HitboxGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);

        // Currently, hitboxes are independent of scale.
        // Thus, we have to undo any scaling from our parent.
        // Otherwise, the shown hitbox will be shown scaled although it is not scaled in the physics world.
        const glm::mat4 undoParentScale = glm::scale(1.f / getOwner()->getTransformation().getAbsoluteScale());

        const std::shared_ptr<Shader> shader = getShader();
        const glm::mat4 & parentTransform = renderOptions.getTransformationMatrix();
        renderOptions.setTransformationMatrix(parentTransform * undoParentScale * trafo);

        shader->setUniform("color", fillColor);
        shapeNode.render(renderOptions);

        shader->setUniform("color", borderColor);
        frameNode.render(renderOptions);

        renderOptions.setTransformationMatrix(parentTransform);
    }
}