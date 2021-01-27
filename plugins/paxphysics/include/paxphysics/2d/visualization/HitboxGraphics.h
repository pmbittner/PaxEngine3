//
// Created by Paul Bittner on 27.01.2021.
//

#ifndef MESHFOLD_HITBOXGRAPHICS_H
#define MESHFOLD_HITBOXGRAPHICS_H

#include <paxcore/rendering/Graphics.h>
#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>
#include "../Fixture2D.h"

namespace PAX::Physics {
    class HitboxGraphics : public Graphics {
        PAX_PROPERTY(HitboxGraphics, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

        static std::shared_ptr<Shader> rectangleShader;

        Fixture2D & fixture;
        TransformationNode trafoNode;
        MeshNode meshNode;

        static void initShaders();

    public:
        explicit HitboxGraphics(Fixture2D & fixture);
        ClassMetadata getMetadata() override;
        void render(RenderOptions &renderOptions) override;
    };
}

#endif //MESHFOLD_HITBOXGRAPHICS_H
