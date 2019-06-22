//
// Created by paul on 29.12.18.
//

#ifndef PAXENGINE3_RENDERPASS_H
#define PAXENGINE3_RENDERPASS_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>
#include "RenderPassChannel.h"

namespace PAX {
    class RenderPass : public SceneGraph {
    public:
        RenderPass();
        ~RenderPass() override;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        /*
        virtual const std::unique_ptr<RenderPassChannel> & addChannel(RenderPassChannel::Format format, RenderPassChannel::ValueType valueType) = 0;
        virtual const std::unique_ptr<RenderPassChannel> & getChannel(int id) const = 0;
         */

        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_RENDERPASS_H
