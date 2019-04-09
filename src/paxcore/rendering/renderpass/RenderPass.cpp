//
// Created by Bittner on 08.04.2019.
//

#include <paxcore/rendering/renderpass/RenderPass.h>

namespace PAX {
    RenderPass::RenderPass() : SceneGraph() {}
    RenderPass::~RenderPass() = default;

    void RenderPass::render(PAX::RenderOptions &renderOptions) {
        bind();
        SceneGraph::render(renderOptions);
        unbind();
    }
}