//
// Created by Paul on 02.07.2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        OpenGLShader *OpenGLSprite::SpriteShader = nullptr;

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

            SpriteShader = new OpenGLShader("GuiShader",
                                          getResourcePath() + "shader/gui/PlainTexture.vert",
                                          getResourcePath() + "shader/gui/PlainTexture.frag");
        }

        OpenGLSprite::OpenGLSprite(OpenGLTexture2D *texture) : Sprite(texture, QuadMesh, SpriteShader) {
            ul_projection = glGetUniformLocation(SpriteShader->getID(), "projection");
            ul_modelview = glGetUniformLocation(SpriteShader->getID(), "modelview");
            ul_texture = glGetUniformLocation(SpriteShader->getID(), "textureSampler");
        }

        void OpenGLSprite::render(RenderOptions &renderOptions) {
            Shader *shader = getShader();
            renderOptions.getShaderOptions().useShader(this, shader);

            Camera *cam = renderOptions.getCamera();
            glm::mat4 model = getOwner()->getTransform().toWorldMatrix();
            const glm::mat4 &view = cam->getViewTransform();
            glm::mat4 modelview = view * model;

            glUniformMatrix4fv(ul_modelview, 1, GL_FALSE, glm::value_ptr(modelview));
            glUniformMatrix4fv(ul_projection, 1, GL_FALSE, glm::value_ptr(cam->getProjection()->toMatrix()));

            if (PAX_OPENGL_doesUniformExist(ul_texture)) {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(ul_texture, 0);
            }

            Sprite::render(renderOptions);

            renderOptions.getShaderOptions().unuseShader(this);
        }
    }
}