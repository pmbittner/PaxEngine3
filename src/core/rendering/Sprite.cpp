//
// Created by Paul on 30.06.2017.
//

#include "../../../include/core/rendering/Sprite.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    Sprite::Sprite(Texture *texture, Mesh *mesh, Shader *shader) : _texture(texture), _mesh(mesh), _shader(shader) {}

    void Sprite::render(RenderOptions &renderOptions) {
        _texture->bind();
        _mesh->render(renderOptions);
        _texture->unbind();
    }

    Shader *Sprite::getShader() const {
        return _shader;
    }

    Texture *Sprite::getTexture() const {
        return _texture;
    }

    Mesh *Sprite::getMesh() const {
        return _mesh;
    }
}