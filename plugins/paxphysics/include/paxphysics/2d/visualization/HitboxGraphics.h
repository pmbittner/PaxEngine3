//
// Created by Paul Bittner on 27.01.2021.
//

#ifndef MESHFOLD_HITBOXGRAPHICS_H
#define MESHFOLD_HITBOXGRAPHICS_H

#include <paxcore/rendering/Graphics.h>
#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>
#include <paxphysics/2d/shape/Shape2D.h>

namespace PAX::Physics {
    class HitboxGraphics : public Graphics {
        PAX_PROPERTY(HitboxGraphics, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

        static std::shared_ptr<Shader> rectangleShader;
        static std::shared_ptr<Mesh> GetRectangleMesh();
        static std::shared_ptr<Mesh> GetRectangleBorderMesh();
        static std::shared_ptr<Mesh> GetCircleMesh();
        static std::shared_ptr<Mesh> GetCircleBorderMesh();

        glm::mat4 trafo;
        MeshNode shapeNode, frameNode;
        glm::vec4 fillColor;
        glm::vec4 borderColor;

        static void initShaders();

    public:
        static const glm::vec4 & GetDefaultFillColorFor(bool isTriggerArea, MotionType m, const Shape2D & fixture);
        static const glm::vec4 & GetDefaultBorderColorFor(bool isTriggerArea, MotionType m, const Shape2D & fixture);

        explicit HitboxGraphics(bool isTriggerArea, const Shape2D & shape, MotionType m);
        ClassMetadata getMetadata() override;
        void render(RenderOptions &renderOptions) override;

        PAX_NODISCARD const glm::vec4 &getFillColor() const;
        void setFillColor(const glm::vec4 &fillColor);
        PAX_NODISCARD const glm::vec4 &getBorderColor() const;
        void setBorderColor(const glm::vec4 &borderColor);
    };
}

#endif //MESHFOLD_HITBOXGRAPHICS_H
