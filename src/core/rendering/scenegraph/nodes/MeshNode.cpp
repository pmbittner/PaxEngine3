//
// Created by Paul on 07.12.2017.
//

#include <core/rendering/scenegraph/nodes/MeshNode.h>

namespace PAX {
    MeshNode::MeshNode(Mesh *mesh) : _mesh(mesh) {
        PAX_assertNotNull(mesh, "Mesh can't be null!")
    }

    void MeshNode::render(RenderOptions &renderOptions) {
        _mesh->render(renderOptions);
        SceneGraph::render(renderOptions);
    }

    Mesh *MeshNode::getMesh() const {
        return _mesh;
    }
}