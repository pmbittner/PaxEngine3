//
// Created by Paul on 02.09.2018.
//

#include <core/rendering/data/Material.h>

void PAX::Material::applyTo(const std::shared_ptr <PAX::Shader> &shader) {
    shader->setUniform("material_diffuse_color", diffuse.color);
    shader->setUniform("material_specular_color", specular.color);
    shader->setUniform("material_specular_exponent", specular.exponent);
    shader->setUniform("material_ambient_color", ambient.color);
    shader->setUniform("material_transparency", transparency);

    if (diffuse.texture)
        diffuse.texture->bind();
}

void PAX::Material::cacheUniformsFor(std::shared_ptr<PAX::Shader> &shader) {
    shader->cacheUniforms({
        "material_diffuse_color",
        "material_specular_color",
        "material_specular_exponent",
        "material_ambient_color",
        "material_transparency"
    });
}