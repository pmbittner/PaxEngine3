//
// Created by Bittner on 08.04.2019.
//

#include <paxcore/rendering/renderpass/RenderPassChannel.h>
#include <cassert>

namespace PAX {
    RenderPassChannel::RenderPassChannel(PAX::RenderPassChannel::Format format,
                                         PAX::RenderPassChannel::ValueType valueType)
                                         : format(format), valueType(valueType)
                                         {

    }

    RenderPassChannel::~RenderPassChannel() = default;

    void RenderPassChannel::attached(PAX::RenderPass *renderPass) {
        assert(!this->renderPass);
        this->renderPass = renderPass;
    }

    void RenderPassChannel::detached(PAX::RenderPass *renderPass) {
        if (this->renderPass == renderPass) {
            this->renderPass = nullptr;
        }
    }

    RenderPassChannel::Format RenderPassChannel::getFormat() const {
        return format;
    }

    RenderPassChannel::ValueType RenderPassChannel::getValueType() const {
        return valueType;
    }

    int RenderPassChannel::getID() const {
        return id;
    }

    RenderPass* RenderPassChannel::getRenderPass() const {
        return renderPass;
    }
}