//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_CUBE_H
#define PAXENGINE3_CUBE_H

#include <utility/lib/GlmIncludes.h>
#include <core/entity/Entity.h>
#include <core/service/Services.h>

namespace PAX {
    namespace Util {
        std::shared_ptr<Mesh> createCube(bool withTexCoords = false)
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

            glm::vec3 objCenter(0, 0, 0);
            std::vector<glm::vec3> normals;
            for (glm::vec3 &vertex : vertices) {
                normals.push_back(glm::normalize(vertex - objCenter));
            }

            std::shared_ptr<Mesh> mesh = Services::GetFactory().create<Mesh>(&vertices, &faces);
            //mesh->addAttribute(normals);

            if (withTexCoords) {
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

                mesh->addAttribute(texCoords);
            }

            return mesh;
        }
    }
}

#endif //PAXENGINE3_CUBE_H
