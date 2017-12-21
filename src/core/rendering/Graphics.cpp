//
// Created by Paul on 28.05.2017.
//

#include "../../../include/core/rendering/Graphics.h"
#include "../../../include/core/entity/Entity.h"

namespace PAX {
    void Graphics::render(RenderOptions &renderOptions) {
        renderOptions.setTransformation(getOwner()->getTransform());
    }

    std::shared_ptr<Shader>& Graphics::getShader() {
        return _shader;
    }

    void Graphics::setShader(const std::shared_ptr<Shader> &shader) {
        GraphicsShaderChangedEvent e(_shader, shader, this);
        Graphics::_shader = shader;
        OnShaderChanged(e);
    }
}