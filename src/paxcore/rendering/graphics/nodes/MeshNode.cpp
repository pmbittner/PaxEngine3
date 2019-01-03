//
// Created by Paul on 07.12.2017.
//

#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/rendering/camera/Camera.h>

namespace PAX {
    MeshNode::MeshNode(const std::shared_ptr<Mesh> & mesh) : _mesh(mesh) {
        PAX_assertNotNull(mesh, "Mesh can't be null!")
    }

    void MeshNode::render(RenderOptions &renderOptions) {
        const std::shared_ptr<Shader> shader = renderOptions.getShaderOptions().getShader();

        const glm::mat4 &view = renderOptions.getViewMatrix();
        glm::mat4 modelview = view * renderOptions.getTransformationMatrix();

        shader->setUniform("modelview", modelview, false);
        shader->setUniform("projection", renderOptions.getProjectionMatrix(), false);
        shader->setUniform("view", view, false);
        shader->setUniform("transposedInvModelView", glm::inverse(modelview), true /* transpose */);

        _mesh->render(renderOptions);

        SceneGraph::render(renderOptions);
    }

    std::shared_ptr<Mesh> MeshNode::getMesh() const {
        return _mesh;
    }
}