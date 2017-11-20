//
// Created by Paul on 30.06.2017.
//

#include "core/rendering/TexturedMesh.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    TexturedMesh::TexturedMesh(Texture *texture, Mesh *mesh) : _texture(texture), _mesh(mesh) {
        PAX_assertNotNull(texture, "Texture can't be null!")
        PAX_assertNotNull(mesh, "Mesh can't be null!")
    }

    void TexturedMesh::render(RenderOptions &renderOptions) {
        _texture->bind();
        _mesh->render(renderOptions);
        _texture->unbind();
    }

    Texture *TexturedMesh::getTexture() const {
        return _texture;
    }

    Mesh *TexturedMesh::getMesh() const {
        return _mesh;
    }
}