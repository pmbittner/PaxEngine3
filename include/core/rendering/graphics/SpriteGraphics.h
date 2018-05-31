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
#include <core/entity/event/SizeChangedEvent.h>

namespace PAX {
    class SpriteGraphics : public SceneGraphGraphics {
        PAX_ENTITYCOMPONENT_BODY(SceneGraphGraphics, false)

        static std::shared_ptr<Mesh> QuadMesh;
        static std::shared_ptr<Mesh> GetMesh();

    protected:
        TransformationNode _trafoNode;
        TexturingNode _textureNode;
        MeshNode _meshNode;

        std::shared_ptr<Texture> _texture;

        void onSizeChanged(SizeChangedEvent& event);
        virtual void registerFlags(Shader::Flags &flags);
        virtual glm::vec2 getSpriteSize() const;

    public:
        SpriteGraphics(const std::shared_ptr<Texture> &texture);

        virtual void setShader(std::shared_ptr<Shader> &shader);
        virtual void attached(Entity *entity) override;
        virtual void detached(Entity *entity) override;
    };
}

#endif //PAXENGINE3_SPRITEGRAPHICS_H
