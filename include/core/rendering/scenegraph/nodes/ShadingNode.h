//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_SHADINGNODE_H
#define PAXENGINE3_SHADINGNODE_H

#include "core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    class ShadingNode : public SceneGraph {
        Shader *shader = nullptr;
        ShaderPriority priority = ShaderPriority::MUTABLE;

    public:
        ShadingNode();
        virtual ~ShadingNode();

        Shader *getShader() const;
        void setShader(Shader *shader);

        ShaderPriority getPriority() const;
        void setPriority(ShaderPriority priority);

        virtual void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_SHADINGNODE_H
