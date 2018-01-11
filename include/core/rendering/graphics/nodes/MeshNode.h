//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_MESHGRAPHICS_H
#define PAXENGINE3_MESHGRAPHICS_H

#include <core/rendering/Graphics.h>
#include <core/rendering/resource/Mesh.h>
#include <core/rendering/resource/Shaded.h>

namespace PAX {
    class MeshNode : public SceneGraph, public Shaded {
        Mesh *_mesh;

    public:
        MeshNode(Mesh *mesh);

        Mesh *getMesh() const;

        virtual void render(RenderOptions &options) override;
        virtual void registerFlags(Shader::Flags &flags);
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_MESHGRAPHICS_H
