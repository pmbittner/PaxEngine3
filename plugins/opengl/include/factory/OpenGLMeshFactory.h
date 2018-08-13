//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGLMESHFACTORY_H
#define PAXENGINE3_OPENGLMESHFACTORY_H

#include <core/rendering/resource/Mesh.h>
#include <core/service/Factory.h>
#include "../resource/OpenGLMesh.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLMeshFactory :
                public Factory<Mesh, std::vector<glm::vec3>*, std::vector<std::vector<int>>*>,
                public Factory<Mesh, std::vector<glm::vec3>*, std::vector<glm::ivec3>*>
        {
        public:

            virtual std::shared_ptr<Mesh> create(std::vector<glm::vec3> *vertices, std::vector<std::vector<int>> *faces) override {
                return std::make_shared<OpenGLMesh>(*vertices, *faces);
            }

            virtual std::shared_ptr<Mesh> create(std::vector<glm::vec3> *vertices, std::vector<glm::ivec3> *faces) override {
                return std::make_shared<OpenGLMesh>(*vertices, *faces);
            }
        };
    }
}

#endif //PAXENGINE3_OPENGLMESHFACTORY_H
