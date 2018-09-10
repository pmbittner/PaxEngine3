//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_MESHNODE_H
#define PAXENGINE3_MESHNODE_H

#include <paxcore/rendering/Graphics.h>
#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/interface/Shaded.h>

namespace PAX {
    class MeshNode : public SceneGraph, public Shaded {
        std::shared_ptr<Mesh> _mesh;

    public:
        MeshNode(std::shared_ptr<Mesh> mesh);

        std::shared_ptr<Mesh> getMesh() const;

        virtual void render(RenderOptions &options) override;
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader) override;
    };
}

#endif //PAXENGINE3_MESHNODE_H
