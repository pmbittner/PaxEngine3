//
// Created by Paul on 30.06.2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../include/opengl/OpenGLMacros.h"
#include "../../include/opengl/OpenGLTexturedMesh.h"
#include "../../include/opengl/resource/OpenGLMesh.h"
#include "../../include/core/entity/Entity.h"
#include "../../include/core/rendering/camera/Camera.h"

namespace PAX {
    namespace OpenGL {
        void checkUniformLocationExistence(std::string uniformName, GLint uniformLocation) {
            if (!PAX_OPENGL_doesUniformExist(uniformLocation)) {
                LOG(WARNING) << "The uniform " << uniformName << " could not be found!";
            }
        }

        OpenGLTexturedMesh::OpenGLTexturedMesh(OpenGLTexture2D *texture, OpenGLMesh *mesh, OpenGLShader *shader) : Sprite(texture, mesh, shader) {
            ul_projection = glGetUniformLocation(shader->getID(), "projection");
            ul_modelview = glGetUniformLocation(shader->getID(), "modelview");

            std::string ulName = "view";
            ul_view = glGetUniformLocation(shader->getID(), ulName.c_str());
            checkUniformLocationExistence(ulName, ul_view);

            ulName = "transposedInvModelView";
            ul_transposedInvModelView = glGetUniformLocation(shader->getID(), ulName.c_str());
            checkUniformLocationExistence(ulName, ul_transposedInvModelView);

            ulName = "textureSampler";
            ul_texture = glGetUniformLocation(shader->getID(), ulName.c_str());
            checkUniformLocationExistence(ulName, ul_texture);

            ulName = "mat_diffuseColor";
            ul_matClr = glGetUniformLocation(shader->getID(), ulName.c_str());
            checkUniformLocationExistence(ulName, ul_matClr);
        }

        void OpenGLTexturedMesh::render(RenderOptions &renderOptions) {
            Shader *shader = getShader();
            renderOptions.setShader(shader);

            shader->bind();

            Camera *cam = renderOptions.getCamera();
            glm::mat4 model = getOwner()->getTransform().toWorldMatrix();
            const glm::mat4 &view = cam->getViewTransform();
            glm::mat4 modelview = view * model;

            /*
            std::cout << "[" << std::endl;
            for (int row = 0; row < 4;++row) {
                std::cout << "    " << view[row].x << " " << view[row].y << " " << view[row].z << " " << view[row].w << " " << std::endl;
            }
            std::cout << "]" << std::endl;
             //*/

            glUniformMatrix4fv(ul_modelview, 1, GL_FALSE, glm::value_ptr(modelview));
            glUniformMatrix4fv(ul_projection, 1, GL_FALSE, glm::value_ptr(cam->getProjection()->toMatrix()));

            if (PAX_OPENGL_doesUniformExist(ul_view)) {
                glUniformMatrix4fv(ul_view, 1, GL_FALSE, glm::value_ptr(view));
            }

            if (PAX_OPENGL_doesUniformExist(ul_transposedInvModelView)) {
                glm::mat4 invModelview = glm::inverse(modelview);
                //GL_TRUE handles transposition here
                glUniformMatrix4fv(ul_transposedInvModelView, 1, GL_TRUE, glm::value_ptr(invModelview));
            }

            if (PAX_OPENGL_doesUniformExist(ul_matClr)) {
                glUniform3fv(ul_matClr, 1, glm::value_ptr(_color));
            }

            if (PAX_OPENGL_doesUniformExist(ul_texture)) {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(ul_texture, 0);
            }

            Sprite::render(renderOptions);

            shader->unbind();
        }
    }
}