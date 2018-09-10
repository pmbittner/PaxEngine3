//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_RENDERFACTORY_H
#define PAXENGINE3_RENDERFACTORY_H

#include <paxcore/world/scenegraph/WorldLayerSceneGraph.h>
#include <paxcore/rendering/data/Mesh.h>

namespace PAX {
    class SceneGraphGenerator;
    class WorldLayer;

    class RenderFactory {
    public:
        virtual WorldLayerSceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer, float z) = 0;
        virtual SceneGraphGenerator* createDefaultSceneGraphGenerator() = 0;

        virtual Mesh* createMesh(std::vector<glm::vec3> &vertices, std::vector<std::vector<int>> &faces) = 0;
        virtual Mesh* createMesh(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> &faces) = 0;
    };
}

#endif //PAXENGINE3_RENDERFACTORY_H
