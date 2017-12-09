//
// Created by bittner on 11/20/17.
//

#include <generation/terrain/Terrain.h>
#include <core/rendering/camera/Camera.h>
#include <iostream>

namespace PAX {
    Terrain::Terrain(Mesh *mesh) : mesh(mesh) {

    }

    void Terrain::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);

        Shader *shader = renderOptions.getShaderOptions().getShader();

        Camera *cam = renderOptions.getCamera();
        glm::mat4 model = renderOptions.getTransformation().toWorldMatrix();
        const glm::mat4 &view = cam->getViewTransform();
        glm::mat4 modelview = view * model;

        shader->setUniform("modelview", modelview);
        shader->setUniform("projection", cam->getProjection()->toMatrix());

        mesh->render(renderOptions);
    }
}