//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_CUBE_H
#define PAXENGINE3_CUBE_H

#include <glm/gtc/type_ptr.hpp>
#include "../../opengl/resource/OpenGLMesh.h"
#include "../../core/entity/Entity.h"
#include "../../opengl/resource/OpenGLTexture2D.h"
#include "../../sdl/utitlity/Path.h"
#include "../../opengl/OpenGLTexturedMesh.h"
#include "../../opengl/test.h"

namespace PAX {
    namespace Demo {
        OpenGL::OpenGLMesh* createCube()
        {
            std::vector<glm::vec3> vertices = {
                    {-0.5f,0.5f,-0.5f},
                    {-0.5f,-0.5f,-0.5f},
                    {0.5f,-0.5f,-0.5f},
                    {0.5f,0.5f,-0.5f},
                    {-0.5f,0.5f,0.5f},
                    {-0.5f,-0.5f,0.5f},
                    {0.5f,-0.5f,0.5f},
                    {0.5f,0.5f,0.5f}
            };

            std::vector<std::vector<int>> faces = {
                    {0,1,3},
                    {3,1,2},
                    {4,5,7},
                    {7,5,6},
                    {3,2,7},
                    {7,2,6},
                    {0,1,4},
                    {4,1,5},
                    {4,0,7},
                    {7,0,3},
                    {5,1,6},
                    {6,1,2}
            };

            float relativeWidth = 1;//(float)texture.Width / (float)texture.ActualWidth;
            float relativeHeight = 1;//(float)texture.Height / (float)texture.ActualHeight;

            std::vector<glm::vec2> texCoords = {
                    {relativeWidth,0},
                    {relativeWidth,relativeHeight},
                    {0,relativeHeight},
                    {0,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0}
            };

            glm::vec3 objCenter(0, 0, 0);
            std::vector<glm::vec3> normals;
            for (glm::vec3 &vertex : vertices) {
                normals.push_back(glm::normalize(vertex - objCenter));
            }

            OpenGL::OpenGLMesh *mesh = new OpenGL::OpenGLMesh(vertices, faces);
            mesh->addAttribute(texCoords);
            mesh->addAttribute(normals);

            return mesh;
        }

        Entity* createCubeEntity(glm::vec3 color, std::string texture = "") {
            std::ostringstream nameStream;
            nameStream << "Cube " << color.x << ", " << color.y << ", " << color.z;
            Entity *e = new Entity(nameStream.str());

            static std::string res = getResourcePath();

            static OpenGL::OpenGLTexture2D *defaultTexture = new OpenGL::OpenGLTexture2D(res + "img/White16.png");
            static OpenGL::OpenGLMesh *mesh = createCube();
            if (!mesh->isFinalized()) {
                mesh->finalize();
                mesh->upload();
            }

            OpenGL::OpenGLTexture2D *tex;
            OpenGL::OpenGLShader *shader = nullptr;
            if (!texture.empty()) {
                tex = new OpenGL::OpenGLTexture2D(res + texture);
            } else {
                tex = defaultTexture;
            }

            shader = new OpenGL::OpenGLShader("Lambert", res + "shader/test/lambert/SingleColor.vert", res + "shader/test/lambert/SingleColor.frag");
            shader->bind();
            glUniform3fv(glGetUniformLocation(shader->getID(), "pLightPositions[0]"), 1, glm::value_ptr(glm::vec3(0, 5, 0)));
            glUniform3fv(glGetUniformLocation(shader->getID(), "pLightColors[0]"), 1, glm::value_ptr(glm::vec3(1, 1, 1)));
            glUniform1f(glGetUniformLocation(shader->getID(), "pLightIntensity[0]"), 0.8f);
            shader->unbind();

            OpenGL::OpenGLTexturedMesh *sprite = new OpenGL::OpenGLTexturedMesh(tex, mesh, shader);
            sprite->_color = color;
            e->add<Graphics>(sprite);
            return e;
        }
    }
}

#endif //PAXENGINE3_CUBE_H
