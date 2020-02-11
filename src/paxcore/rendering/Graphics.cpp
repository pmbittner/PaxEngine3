//
// Created by Paul on 28.05.2017.
//

#include <paxcore/rendering/Graphics.h>
#include <paxcore/gameentity/GameEntity.h>
#include <paxutil/reflection/EngineFieldFlags.h>

namespace PAX {
    PAX_PROPERTY_INIT(PAX::Graphics) {}

    ClassMetadata Graphics::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(Field("Shader", paxtypeof(_shader), &_shader, Field::IsMandatory | EngineFieldFlags::IsResource));
        return m;
    }

    Graphics::~Graphics() = default;

    void Graphics::registerFlags(Shader::Flags &flags) {}

    Shader::Flags Graphics::getShaderFlags() {
        Shader::Flags flags;
        registerFlags(flags);
        return flags;
    }

    std::shared_ptr<Shader>& Graphics::getShader() {
        return _shader;
    }

    void Graphics::setShader(const std::shared_ptr<Shader> &shader) {
        GraphicsShaderChangedEvent e(_shader, shader, this);
        Graphics::_shader = shader;
        OnShaderChanged(e);
    }

    void Graphics::render(RenderOptions &renderOptions) {
        renderOptions.setTransformationMatrix(getOwner()->getTransformation().getWorldMatrix());
    }
}