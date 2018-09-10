//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_TEST_H
#define PAXENGINE3_TEST_H

#include <GL/glew.h>
#include "core/rendering/Graphics.h"
#include "opengl/resource/OpenGLMesh.h"
#include "opengl/resource/OpenGLShader.h"

namespace PAX {
    namespace OpenGL {
        class test : public Graphics {
            OpenGLMesh *mesh;
            OpenGLShader *shader;

        public:

            test() {
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

                mesh = new OpenGLMesh(vertices, indices);
                mesh->finalize();
                mesh->upload();

                shader = new OpenGLShader("ThinMatrix",
                                          Services::GetPaths().RelativeResourcePath() + "shader/test/thinmatrix/tut5.vert",
                                          Services::GetPaths().RelativeResourcePath() + "shader/test/thinmatrix/tut5.frag"
                );
            }

            virtual void render(RenderOptions &options) override {
                std::cout << " 1 " << std::endl;
                shader->bind();
                std::cout << " 2 " << std::endl;

                glBindVertexArray(mesh->getID());
                std::cout << " 3 " << std::endl;
                glEnableVertexAttribArray(0);
                std::cout << " 4 " << std::endl;
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
                std::cout << " 5 " << std::endl;
                glDisableVertexAttribArray(0);
                std::cout << " 6 " << std::endl;
                glBindVertexArray(0);
                std::cout << " 7 " << std::endl;

                shader->unbind();
            }
        };
    }
}

#endif //PAXENGINE3_TEST_H
