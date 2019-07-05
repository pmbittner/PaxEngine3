//
// Created by Paul on 02.09.2018.
//

#include <paxcore/rendering/data/Material.h>
#include <iostream>

PAX::Material::Material(const std::string &name) : name(name) {}

void PAX::Material::applyTo(PAX::Shader* shader) {
    shader->setUniform("material_diffuse_color", diffuse.color);
    shader->setUniform("material_specular_color", specular.color);
    shader->setUniform("material_specular_exponent", specular.exponent);
    shader->setUniform("material_ambient_color", ambient.color);
    shader->setUniform("material_opacity", opacity);
    shader->setUniform("material_hasDiffuseTexture", diffuse.texture.operator bool());

    if (diffuse.texture)
        diffuse.texture->bind();
}

void PAX::Material::unapplyFrom(PAX::Shader *shader) {
    if (diffuse.texture)
        diffuse.texture->unbind();
}