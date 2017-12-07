//
// Created by Paul on 30.06.2017.
//

#include "core/rendering/scenegraph/nodes/TexturingNode.h"
#include "lib/easylogging++.h"

namespace PAX {
    TexturingNode::TexturingNode(Texture *texture) : _texture(texture) {
        PAX_assertNotNull(texture, "Texture can't be null!")
    }

    void TexturingNode::render(RenderOptions &renderOptions) {
        _texture->bind();
        SceneGraph::render(renderOptions);
        _texture->unbind();
    }

    Texture *TexturingNode::getTexture() const {
        return _texture;
    }
}