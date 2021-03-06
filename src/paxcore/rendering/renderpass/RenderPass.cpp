//
// Created by Bittner on 08.04.2019.
//

#include <paxcore/rendering/renderpass/RenderPass.h>

namespace PAX {
    RenderPass::RenderPass(const glm::ivec2 & resolution) : SceneGraph(), resolution(resolution) {}
    RenderPass::~RenderPass() = default;

    const glm::ivec2 & RenderPass::getResolution() const {
        return resolution;
    }

    void RenderPass::setClearColour(const Colour &colour) {
        this->clearColour = colour;
    }

    const Colour & RenderPass::getClearColour() const {
        return clearColour;
    }

    void RenderPass::addChannel(PAX::RenderPassChannel renderPassChannel) {
        channels.push_back(renderPassChannel);
    }

    const RenderPassChannel & RenderPass::getChannel(const std::string &name) const {
        for (const RenderPassChannel & c : channels) {
            if (c.getName() == name) {
                return c;
            }
        }
        PAX_THROW_RUNTIME_ERROR("There is no RenderPassChannel with the given name \"" << name << "\"!");
    }

    const std::vector<RenderPassChannel>& RenderPass::getChannels() const {
        return channels;
    }

    void RenderPass::finalize() {
        for (RenderPassChannel & c : channels) {
            c.initialize(this);
        }
    }
}