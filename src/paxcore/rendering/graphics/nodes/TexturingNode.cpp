//
// Created by Paul on 30.06.2017.
//

#include <paxcore/rendering/scenegraph/nodes/TexturingNode.h>
#include <polypropylene/log/Errors.h>

namespace PAX {
    TexturingNode::TexturingNode(const std::shared_ptr<Texture> &texture) : _texture(texture) {

    }

    void TexturingNode::render(RenderOptions &renderOptions) {
        const bool hasTexture = _texture != nullptr;
        if (hasTexture)
            _texture->bind();

        SceneGraph::render(renderOptions);

        if (hasTexture)
            _texture->unbind();
    }

    void TexturingNode::setTexture(const std::shared_ptr<Texture> &texture) {
        _texture = texture;
    }

    const std::shared_ptr<Texture>& TexturingNode::getTexture() const {
        return _texture;
    }
}