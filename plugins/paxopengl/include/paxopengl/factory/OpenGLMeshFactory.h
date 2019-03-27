//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGLMESHFACTORY_H
#define PAXENGINE3_OPENGLMESHFACTORY_H

#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include "../resource/OpenGLMesh.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLMeshFactory : public MeshFactory {
        public:
            std::shared_ptr<Mesh> create(const std::vector<glm::vec3> & vertices, const std::vector<glm::ivec3> & faces) override {
                return std::make_shared<OpenGLMesh>(vertices, faces);
            }

            std::shared_ptr<Mesh> create(const std::vector<glm::vec2> & vertices, const std::vector<glm::ivec3> & faces) override {
                return std::make_shared<OpenGLMesh>(vertices, faces);
            }
        };
    }
}

#endif //PAXENGINE3_OPENGLMESHFACTORY_H
