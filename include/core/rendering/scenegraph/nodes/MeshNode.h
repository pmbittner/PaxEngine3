//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_MESHGRAPHICS_H
#define PAXENGINE3_MESHGRAPHICS_H

#include <core/rendering/Graphics.h>
#include <core/rendering/resource/Mesh.h>

namespace PAX {
    class MeshNode : public SceneGraph {
        Mesh *_mesh;

    public:
        MeshNode(Mesh *mesh);
        virtual void render(RenderOptions &options) override;

        Mesh *getMesh() const;
    };
}

#endif //PAXENGINE3_MESHGRAPHICS_H
