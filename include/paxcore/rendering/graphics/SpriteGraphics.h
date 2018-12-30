//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITEGRAPHICS_H
#define PAXENGINE3_SPRITEGRAPHICS_H

#include <paxcore/rendering/data/Texture.h>
#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/rendering/scenegraph/nodes/TexturingNode.h>
#include <paxcore/entity/event/SizeChangedEvent.h>

namespace PAX {
    class SpriteGraphics : public SceneGraphGraphics {
    PAX_PROPERTY_DERIVES(SceneGraphGraphics)
    PAX_PROPERTY_IS_SINGLE

        static std::shared_ptr<Mesh> QuadMesh;
        static std::shared_ptr<Mesh> GetMesh();

    protected:
        TransformationNode _trafoNode;
        TexturingNode _textureNode;
        MeshNode _meshNode;

        std::shared_ptr<Texture> _texture;

        void onSizeChanged(SizeChangedEvent& event);
        virtual glm::vec2 getSpriteSize() const;

    public:
        SpriteGraphics(const std::shared_ptr<Texture> &texture);

        virtual void attached(Entity &entity) override;
        virtual void detached(Entity &entity) override;
    };
}

#endif //PAXENGINE3_SPRITEGRAPHICS_H
