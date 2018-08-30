//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_MESHGRAPHICS_H
#define PAXENGINE3_MESHGRAPHICS_H

#include <core/rendering/Graphics.h>
#include <core/rendering/data/Mesh.h>
#include <core/rendering/interface/Shaded.h>

namespace PAX {
    class MeshNode : public SceneGraph, public Shaded {
        std::shared_ptr<Mesh> _mesh;

    public:
        MeshNode(std::shared_ptr<Mesh> mesh);

        std::shared_ptr<Mesh> getMesh() const;

        virtual void render(RenderOptions &options) override;
        virtual void registerFlags(Shader::Flags &flags);
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_MESHGRAPHICS_H
