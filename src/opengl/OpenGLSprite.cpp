//
// Created by Paul on 30.06.2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../include/opengl/OpenGLSprite.h"
#include "../../include/opengl/resource/OpenGLMesh.h"
#include "../../include/core/entity/Entity.h"
#include "../../include/core/rendering/camera/Camera.h"

namespace PAX {
    namespace OpenGL {
        OpenGLSprite::OpenGLSprite(OpenGLTexture2D *texture, OpenGLMesh *mesh, OpenGLShader *shader) : Sprite(texture, mesh, shader) {
            ul_projection = glGetUniformLocation(shader->getID(), "projection");
            ul_modelview = glGetUniformLocation(shader->getID(), "modelview");
            ul_texture = glGetUniformLocation(shader->getID(), "textureSampler");
        }

        void OpenGLSprite::render(RenderOptions &renderOptions) {
            Shader *shader = getShader();
            renderOptions.setShader(shader);

            shader->bind();

            Camera *cam = renderOptions.getCamera();
            glm::mat4 model = getOwner()->getTransform().toWorldMatrix();
            const glm::mat4 &view = cam->getViewTransform();
            glm::mat4 modelview = view * model;

            glUniformMatrix4fv(ul_modelview, 1, GL_FALSE, glm::value_ptr(modelview));
            glUniformMatrix4fv(ul_projection, 1, GL_FALSE, glm::value_ptr(cam->getProjection()->toMatrix()));

            glActiveTexture(GL_TEXTURE0);
            glUniform1i(ul_texture, 0);
            Sprite::render(renderOptions);

            shader->unbind();
        }
    }
}