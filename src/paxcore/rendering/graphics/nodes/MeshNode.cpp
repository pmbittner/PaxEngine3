//
// Created by Paul on 07.12.2017.
//

#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/rendering/camera/Camera.h>

namespace PAX {
    MeshNode::MeshNode() = default;

    MeshNode::MeshNode(const std::shared_ptr<Mesh> & mesh) : _mesh(mesh) {
        PAX_ASSERT_NOT_NULL(mesh, "Mesh can't be null!");
    }

    MeshNode::~MeshNode() = default;

    void MeshNode::render(RenderOptions &renderOptions) {
        Shader* shader = renderOptions.getShaderOptions().getShader();

        glm::mat4 modelview = renderOptions.getViewMatrix() * renderOptions.getTransformationMatrix();
        // TODO: Move projection and view setting to the renderoptions as soon as shaders and cam are set.
        shader->setUniform("projection", renderOptions.getProjectionMatrix(), false);
        shader->setUniform("view", renderOptions.getViewMatrix(), false);
        shader->setUniform("modelview", modelview, false);
        shader->setUniform("transposedInvModelView", glm::inverse(modelview), true /* transpose */);

        //if (_mesh)
            _mesh->render(renderOptions);

        SceneGraph::render(renderOptions);
    }

    void MeshNode::setMesh(const std::shared_ptr<Mesh> & mesh) {
        _mesh = mesh;
    }

    const std::shared_ptr<Mesh> & MeshNode::getMesh() const {
        return _mesh;
    }
}