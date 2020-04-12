//
// Created by Bittner on 08.04.2019.
//

#include <paxcore/rendering/renderpass/RenderPassChannel.h>
#include <paxcore/rendering/renderpass/RenderPass.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/TextureFactory.h>

namespace PAX {
    RenderPassChannel::RenderPassChannel(const std::string & name, Texture::PixelFormat format) : name(name), pixelFormat(format) {

    }

    RenderPassChannel::~RenderPassChannel() = default;

    void RenderPassChannel::initialize(PAX::RenderPass *renderPass) {
        const glm::ivec2 & res = renderPass->getResolution();
        auto * tex = Services::GetFactoryService().get<TextureFactory>();
        texture = tex->create(res.x, res.y, pixelFormat, Texture::ColourType::Float);
    }

    const std::shared_ptr<Texture> & RenderPassChannel::getTexture() const {
        return texture;
    }

    const std::string& RenderPassChannel::getName() const {
        return name;
    }
}