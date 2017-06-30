//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_CUBE_H
#define PAXENGINE3_CUBE_H

#include "../../opengl/resource/OpenGLMesh.h"
#include "../../core/entity/Entity.h"
#include "../../opengl/resource/OpenGLTexture2D.h"
#include "../../sdl/utitlity/Path.h"
#include "../../opengl/OpenGLSprite.h"
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
                    {0.5f,0.5f,0.5f},

                    {0.5f,0.5f,-0.5f},
                    {0.5f,-0.5f,-0.5f},
                    {0.5f,-0.5f,0.5f},
                    {0.5f,0.5f,0.5f},

                    {-0.5f,0.5f,-0.5f},
                    {-0.5f,-0.5f,-0.5f},
                    {-0.5f,-0.5f,0.5f},
                    {-0.5f,0.5f,0.5f},

                    {-0.5f,0.5f,0.5f},
                    {-0.5f,0.5f,-0.5f},
                    {0.5f,0.5f,-0.5f},
                    {0.5f,0.5f,0.5f},

                    {-0.5f,-0.5f,0.5f},
                    {-0.5f,-0.5f,-0.5f},
                    {0.5f,-0.5f,-0.5f},
                    {0.5f,-0.5f,0.5f}
            };

            std::vector<std::vector<int>> faces = {
                    {0,1,3},
                    {3,1,2},
                    {4,5,7},
                    {7,5,6},
                    {8,9,11},
                    {11,9,10},
                    {12,13,15},
                    {15,13,14},
                    {16,17,19},
                    {19,17,18},
                    {20,21,23},
                    {23,21,22}
            };

            float relativeWidth = 1;//(float)texture.Width / (float)texture.ActualWidth;
            float relativeHeight = 1;//(float)texture.Height / (float)texture.ActualHeight;

            std::vector<glm::vec2> texCoords = {
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0},
                    {0,0},
                    {0,relativeHeight},
                    {relativeWidth,relativeHeight},
                    {relativeWidth,0}
            };

            OpenGL::OpenGLMesh *mesh = new OpenGL::OpenGLMesh(vertices, faces);
            //mesh->addAttribute(texCoords);

            return mesh;
        }

        Entity* createCubeEntity() {
            Entity *e = new Entity();
            std::string res = getResourcePath();

            //*
            OpenGL::OpenGLTexture2D *tex = new OpenGL::OpenGLTexture2D(res + "img/Crate.png");
            OpenGL::OpenGLMesh *mesh = createCube();
            mesh->finalize();
            mesh->upload();

            OpenGL::OpenGLShader *shader = new OpenGL::OpenGLShader("PlainTexture", res + "shader/test/PlainTexture.vert", res + "shader/test/PlainTexture.frag");

            OpenGL::OpenGLSprite *sprite = new OpenGL::OpenGLSprite(tex, mesh, shader);
            e->add<Graphics>(sprite);
            /*/
            e->add<Graphics>(new OpenGL::test());
            //*/
            return e;
        }
    }
}

#endif //PAXENGINE3_CUBE_H
