//
// Created by Paul on 02.09.2018.
//

#include <core/rendering/graphics/MeshGraphics.h>

namespace PAX {
    MeshGraphics::MeshGraphics(const std::shared_ptr <Mesh> &mesh, const std::shared_ptr <PAX::Material> &material)
    : _meshNode(mesh), _material(material)
    {

    }

    void MeshGraphics::setShader(std::shared_ptr <PAX::Shader> &shader) {
        Super::setShader(shader);
        _material->cacheUniformsFor(shader);
        _meshNode.cacheUniformsFor(shader);
    }

    void MeshGraphics::render(PAX::RenderOptions &renderOptions) {
        Super::render(renderOptions);
        _material->applyTo(renderOptions.getShaderOptions().getShader());
        _meshNode.render(renderOptions);
    }
}