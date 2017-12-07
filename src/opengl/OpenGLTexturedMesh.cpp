//
// Created by Paul on 30.06.2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <core/service/Services.h>
#include "../../include/opengl/OpenGLMacros.h"
#include "../../include/opengl/OpenGLTexturedMesh.h"
#include "../../include/opengl/resource/OpenGLMesh.h"
#include "../../include/core/entity/Entity.h"
#include "../../include/core/rendering/camera/Camera.h"

namespace PAX {
    namespace OpenGL {
        OpenGLTexturedMesh::OpenGLTexturedMesh(OpenGLTexture2D *texture, OpenGLMesh *mesh) : TexturedMesh(texture, mesh) {
            Shader* meshShader = Services::GetResources().loadOrGet<Shader>("", "");
            meshShader->cacheUniforms({
                                              "projection",
                                              "modelview",
                                              "view",
                                              "transposedInvModelView",
                                              "textureSampler",
                                              "mat_diffuseColor"
                                      });
        }

        void OpenGLTexturedMesh::render(RenderOptions &renderOptions) {
            Shader *shader = renderOptions.getShaderOptions().getShader();

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

            /*
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
             */

            TexturedMesh::render(renderOptions);
        }
    }
}