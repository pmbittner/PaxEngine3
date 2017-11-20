//
// Created by Paul on 02.07.2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <core/Services.h>

#include "../../include/opengl/OpenGLSprite.h"
#include "../../include/opengl/resource/OpenGLMesh.h"
#include "../../include/opengl/resource/OpenGLShader.h"
#include "../../include/opengl/resource/OpenGLTexture2D.h"
#include "../../include/sdl/utitlity/Path.h"

#include "../../include/opengl/OpenGLMacros.h"
#include "../../include/core/entity/Entity.h"
#include "../../include/core/rendering/camera/Camera.h"

namespace PAX {
    namespace OpenGL {
        OpenGLMesh *OpenGLSprite::QuadMesh = nullptr;

        void OpenGLSprite::Initialize() {
            std::vector<glm::vec3> vertices = {
                    {-0.5f,0.5f,0},   //V0
                    {-0.5f,-0.5f,0},  //V1
                    {0.5f,-0.5f,0},   //V2
                    {0.5f,0.5f,0}     //V3
            };

            std::vector<std::vector<int>> indices = {
                    {0,1,3},  //Top left triangle (V0,V1,V3)
                    {3,1,2}   //Bottom right triangle (V3,V1,V2)
            };

            std::vector<glm::vec2> texCoords = {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {1, 0}
            };

            QuadMesh = new OpenGLMesh(vertices, indices);
            QuadMesh->addAttribute(texCoords);
            QuadMesh->finalize();
            QuadMesh->upload();
        }

        OpenGLSprite::OpenGLSprite(Texture *texture) : TexturedMesh(texture, QuadMesh) {
            Shader* shader = Services::GetResources().loadOrGet<Shader>(
                    (getResourcePath() + "shader/gui/PlainTexture.vert").c_str(),
                    (getResourcePath() + "shader/gui/PlainTexture.frag").c_str()
            );

            shader->cacheUniforms({
                                          "projection",
                                          "modelview",
                                          "textureSampler"
                                  });

            setShader(shader);
        }

        void OpenGLSprite::render(RenderOptions &renderOptions) {
            Shader *shader = renderOptions.getShaderOptions().getShader();

            Camera *cam = renderOptions.getCamera();
            glm::mat4 model = getOwner()->getTransform().toWorldMatrix();
            const glm::mat4 &view = cam->getViewTransform();
            glm::mat4 modelview = view * model;

            shader->setUniform("modelview", modelview);
            shader->setUniform("projection", cam->getProjection()->toMatrix());

            glActiveTexture(GL_TEXTURE0);
            shader->setUniform("textureSampler", 0);

            TexturedMesh::render(renderOptions);
        }
    }
}