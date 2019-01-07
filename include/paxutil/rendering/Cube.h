//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_CUBE_H
#define PAXENGINE3_CUBE_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxcore/entity/Entity.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/factory/MeshFactory.h>

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

            std::vector<glm::ivec3> faces = {
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

            MeshFactory* meshFactory = Services::GetFactoryService().get<MeshFactory>();
            PAX_assertNotNull(meshFactory, "[PAX::Util::createCube] MeshFactory is required, but is not registered!")
            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);

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

                mesh->addAttribute(Mesh::UVs, texCoords);
            }

            { // Create normals
                glm::vec3 objCenter(0, 0, 0);
                std::vector<glm::vec3> normals;
                for (glm::vec3 &vertex : vertices) {
                    normals.push_back(glm::normalize(vertex - objCenter));
                }
                //mesh->addAttribute(Mesh::Normals, normals);
            }

            return mesh;
        }
    }
}

#endif //PAXENGINE3_CUBE_H
