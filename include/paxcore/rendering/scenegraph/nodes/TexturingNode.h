//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SPRITE_H
#define PAXENGINE3_SPRITE_H

#include <memory>

#include <paxcore/rendering/scenegraph/SceneGraph.h>
#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    class TexturingNode : public SceneGraph {
        std::shared_ptr<Texture> _texture;

    public:
        explicit TexturingNode(const std::shared_ptr<Texture> &texture);
        void render(RenderOptions &options) override;

        void setTexture(const std::shared_ptr<Texture> &texture);
        PAX_NODISCARD const std::shared_ptr<Texture>& getTexture() const;
    };
}

#endif //PAXENGINE3_SPRITE_H
