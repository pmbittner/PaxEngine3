//
// Created by Paul on 02.09.2018.
//

#ifndef PAXENGINE3_MESHGRAPHICS_H
#define PAXENGINE3_MESHGRAPHICS_H

#include "../Graphics.h"
#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/data/Material.h>

namespace PAX {
    class MeshGraphics : public Graphics {
        PAX_ENTITYCOMPONENT_BODY(Graphics, false)

    protected:
        MeshNode _meshNode;
        std::shared_ptr<Material> _material;

    public:
        MeshGraphics(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<Material> &material);

        virtual void setShader(std::shared_ptr<Shader> &shader);
        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_MESHGRAPHICS_H_YOLOOOAOAOA
