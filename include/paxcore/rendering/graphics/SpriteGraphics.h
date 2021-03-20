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
#include <paxcore/gameentity/event/SizeChangedEvent.h>

namespace PAX {
    class SpriteGraphics : public SceneGraphGraphics {
        PAX_PROPERTY(SpriteGraphics, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(SceneGraphGraphics)
        PAX_PROPERTY_IS_SINGLE

        static std::shared_ptr<Mesh> QuadMesh;
        static std::shared_ptr<Mesh> GetMesh();

    protected:
        SpriteGraphics();
        void init();

        TransformationNode _trafoNode;
        TexturingNode _textureNode;
        MeshNode _meshNode;

        std::shared_ptr<Texture> _texture = nullptr;

        void onSizeChanged(SizeChangedEvent& event);
        PAX_NODISCARD virtual glm::vec2 getSpriteSize() const;
        void updateSizeProperty();

        void setMesh(const std::shared_ptr<Mesh> & mesh);

    public:
        explicit SpriteGraphics(const std::shared_ptr<Texture> &texture);

        void attached(GameEntity &entity) override;
        void detached(GameEntity &entity) override;

        void render(RenderOptions &renderOptions) override;
        PAX_NODISCARD ClassMetadata getMetadata() override;

        void setTexture(const std::shared_ptr<Texture> &texture);
        PAX_NODISCARD const std::shared_ptr<Texture> & getTexture() const;
        PAX_NODISCARD const std::shared_ptr<Mesh> & getMesh() const;

        void created() override;
    };
}

#endif //PAXENGINE3_SPRITEGRAPHICS_H
