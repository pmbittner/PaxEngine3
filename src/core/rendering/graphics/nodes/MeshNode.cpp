//
// Created by Paul on 07.12.2017.
//

#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/camera/Camera.h>

namespace PAX {
    MeshNode::MeshNode(std::shared_ptr<Mesh> mesh) : _mesh(mesh) {
        PAX_assertNotNull(mesh, "Mesh can't be null!")
    }

    void MeshNode::render(RenderOptions &renderOptions) {
        Shader *shader = renderOptions.getShaderOptions().getShader();

        Camera *cam = renderOptions.getCamera();
        glm::mat4 model = renderOptions.getTransformation();
        const glm::mat4 &view = cam->getViewTransform();
        glm::mat4 modelview = view * model;

        shader->setUniform("modelview", modelview);
        shader->setUniform("projection", cam->getProjection()->toMatrix());
        shader->setUniform("view", view);
        shader->setUniform("transposedInvModelView", glm::inverse(modelview), true /* transpose */);

        _mesh->render(renderOptions);

        SceneGraph::render(renderOptions);
    }

    std::shared_ptr<Mesh> MeshNode::getMesh() const {
        return _mesh;
    }

    void MeshNode::cacheUniformsFor(std::shared_ptr<Shader> &shader) {
        shader->cacheUniforms({
                                     "projection",
                                     "view",
                                     "modelview",
                                     "transposedInvModelView"
                             });
    }

    void MeshNode::registerFlags(Shader::Flags &flags) {}
}