//
// Created by Paul on 30.06.2017.
//

#include <paxcore/rendering/scenegraph/nodes/TexturingNode.h>
#include <paxutil/log/Errors.h>

namespace PAX {
    TexturingNode::TexturingNode(const std::shared_ptr<Texture> &texture) : _texture(texture) {
        PAX_ASSERT_NOT_NULL(texture, "Texture can't be null!");
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