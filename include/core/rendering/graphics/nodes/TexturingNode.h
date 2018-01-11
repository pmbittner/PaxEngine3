//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SPRITE_H
#define PAXENGINE3_SPRITE_H

#include <memory>

#include <core/rendering/scenegraph/SceneGraph.h>
#include <core/rendering/resource/Texture.h>

namespace PAX {
    class TexturingNode : public SceneGraph {
        std::shared_ptr<Texture> _texture;

    public:
        TexturingNode(const std::shared_ptr<Texture> &texture);
        virtual void render(RenderOptions &options) override;

        std::shared_ptr<Texture>& getTexture();
    };
}

#endif //PAXENGINE3_SPRITE_H
