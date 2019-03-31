//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_MESHNODE_H
#define PAXENGINE3_MESHNODE_H

#include <paxcore/rendering/Graphics.h>
#include <paxcore/rendering/data/Mesh.h>

namespace PAX {
    class MeshNode : public SceneGraph {
        std::shared_ptr<Mesh> _mesh;

    public:
        explicit MeshNode(const std::shared_ptr<Mesh> & mesh);

        void setMesh(const std::shared_ptr<Mesh> & mesh);
        std::shared_ptr<Mesh> getMesh() const;

        void render(RenderOptions &options) override;
    };
}

#endif //PAXENGINE3_MESHNODE_H
