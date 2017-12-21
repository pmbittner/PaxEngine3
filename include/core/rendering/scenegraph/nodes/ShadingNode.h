//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_SHADINGNODE_H
#define PAXENGINE3_SHADINGNODE_H

#include <memory>
#include "core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    class ShadingNode : public SceneGraph {
        std::shared_ptr<Shader> _shader = nullptr;
        ShaderPriority _priority = ShaderPriority::MUTABLE;

    public:
        ShadingNode();
        virtual ~ShadingNode();

        std::shared_ptr<Shader>& getShader();
        void setShader(const std::shared_ptr<Shader>& shader);

        ShaderPriority getPriority() const;
        void setPriority(ShaderPriority priority);

        virtual void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_SHADINGNODE_H
