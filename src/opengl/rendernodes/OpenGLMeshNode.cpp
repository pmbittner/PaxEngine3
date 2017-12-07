//
// Created by Paul on 07.12.2017.
//

#include <opengl/rendernodes/OpenGLMeshNode.h>
#include <core/rendering/RenderOptions.h>
#include <core/rendering/resource/Shader.h>
#include <core/rendering/camera/Camera.h>

namespace PAX {
    namespace OpenGL {
        OpenGLMeshNode::OpenGLMeshNode(OpenGLMesh *mesh) : MeshNode(mesh) {
            /*
            Shader* meshShader = Services::GetResources().loadOrGet<Shader>("", "");
            meshShader->cacheUniforms({
                                              "projection",
                                              "modelview",
                                              "view",
                                              "transposedInvModelView",
                                              "textureSampler",
                                              "mat_diffuseColor"
                                      });
                                      */
        }

        void OpenGLMeshNode::render(RenderOptions &renderOptions) {
            Shader *shader = renderOptions.getShaderOptions().getShader();

            Camera *cam = renderOptions.getCamera();
            glm::mat4 model = renderOptions.getTransformation().toWorldMatrix();
            const glm::mat4 &view = cam->getViewTransform();
            glm::mat4 modelview = view * model;

            shader->setUniform("modelview", modelview);
            shader->setUniform("projection", cam->getProjection()->toMatrix());
            shader->setUniform("view", view);
            shader->setUniform("transposedInvModelView", glm::inverse(modelview), true /* transpose */);

            MeshNode::render(renderOptions);
        }
    }
}