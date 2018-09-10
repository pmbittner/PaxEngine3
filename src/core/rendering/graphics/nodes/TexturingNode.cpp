//
// Created by Paul on 30.06.2017.
//

#include <core/rendering/scenegraph/nodes/TexturingNode.h>
#include <easylogging++.h>

namespace PAX {
    TexturingNode::TexturingNode(const std::shared_ptr<Texture> &texture) : _texture(texture) {
        PAX_assertNotNull(texture, "Texture can't be null!")
    }

    void TexturingNode::render(RenderOptions &renderOptions) {
        _texture->bind();
        SceneGraph::render(renderOptions);
        _texture->unbind();
    }

    std::shared_ptr<Texture>& TexturingNode::getTexture() {
        return _texture;
    }
}