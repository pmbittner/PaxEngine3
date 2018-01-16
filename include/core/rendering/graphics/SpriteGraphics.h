//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITEGRAPHICS_H
#define PAXENGINE3_SPRITEGRAPHICS_H

#include <core/rendering/resource/Texture.h>
#include <core/rendering/graphics/SceneGraphGraphics.h>
#include <core/rendering/scenegraph/nodes/TransformationNode.h>
#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/graphics/nodes/TexturingNode.h>

namespace PAX {
    PAX_ENTITYCOMPONENT_DERIVED(SpriteGraphics, SceneGraphGraphics)
    class SpriteGraphics : public SceneGraphGraphics {
        PAX_ENTITYCOMPONENT_BODY
        static Mesh* QuadMesh;
        static Mesh *GetMesh();

    protected:
        TransformationNode _trafoNode;
        TexturingNode _textureNode;
        MeshNode _meshNode;

        std::shared_ptr<Texture> _texture;

        virtual void registerFlags(Shader::Flags &flags);
        virtual void initializeTransformation();

    public:
        SpriteGraphics(const std::shared_ptr<Texture> &texture);

        void setSpriteScale(const glm::vec2& scale);
        virtual void setShader(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_SPRITEGRAPHICS_H
