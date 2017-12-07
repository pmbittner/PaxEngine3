//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SPRITE_H
#define PAXENGINE3_SPRITE_H

#include <core/rendering/scenegraph/SceneGraph.h>
#include <core/rendering/resource/Texture.h>

namespace PAX {
    class TexturingNode : public SceneGraph {
        Texture *_texture;

    public:
        TexturingNode(Texture *texture);
        virtual void render(RenderOptions &options) override;

        Texture *getTexture() const;
    };
}

#endif //PAXENGINE3_SPRITE_H
