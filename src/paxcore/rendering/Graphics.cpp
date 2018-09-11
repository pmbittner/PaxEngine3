//
// Created by Paul on 28.05.2017.
//

#include <paxcore/rendering/Graphics.h>
#include <paxcore/entity/Entity.h>

namespace PAX {
    void Graphics::registerFlags(Shader::Flags &flags) {}

    Shader::Flags Graphics::getShaderFlags() {
        Shader::Flags flags;
        registerFlags(flags);
        return flags;
    }

    std::shared_ptr<Shader>& Graphics::getShader() {
        return _shader;
    }

    void Graphics::setShader(std::shared_ptr<Shader> &shader) {
        GraphicsShaderChangedEvent e(_shader, shader, this);
        Graphics::_shader = shader;
        OnShaderChanged(e);
    }

    void Graphics::render(RenderOptions &renderOptions) {
        renderOptions.setTransformationMatrix(getOwner()->getTransformation().getWorldMatrix());
    }
}