//
// Created by Paul on 11.01.2018.
//

#include <paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h>

namespace PAX {
    SpriteSheetNode::SpriteSheetNode(int columns, int rows) : SceneGraph(), _size(columns, rows) {
        setOffset(0, 0);
    }

    void SpriteSheetNode::setOffset(int xOffset, int yOffset) {
        _offset = {xOffset, yOffset};
    }

    const glm::ivec2 & SpriteSheetNode::getOffset() const {
        return _offset;
    }

    void SpriteSheetNode::setSize(const glm::ivec2 &size) {
        _size = size;
    }

    const glm::ivec2 & SpriteSheetNode::getSize() const {
        return _size;
    }

    void SpriteSheetNode::render(RenderOptions &options) {
        Shader* shader = options.getShaderOptions().getShader();
        shader->setUniform("spriteSheet.offset", _offset);
        shader->setUniform("spriteSheet.size", _size);
        SceneGraph::render(options);
    }
}