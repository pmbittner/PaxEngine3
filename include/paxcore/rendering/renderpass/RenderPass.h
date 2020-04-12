//
// Created by paul on 29.12.18.
//

#ifndef PAXENGINE3_RENDERPASS_H
#define PAXENGINE3_RENDERPASS_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>
#include <paxcore/rendering/data/Colour.h>
#include "RenderPassChannel.h"

namespace PAX {
    class RenderPass : public SceneGraph {
        glm::ivec2 resolution;
        Colour clearColour = Colours::White;
        std::vector<RenderPassChannel> channels;

    public:
        RenderPass(const glm::ivec2 & resolution);
        ~RenderPass() override;

        PAX_NODISCARD const glm::ivec2 & getResolution() const;
        PAX_NODISCARD void setClearColour(const Colour & colour);
        PAX_NODISCARD const Colour & getClearColour() const;

        void addChannel(RenderPassChannel renderPassChannel);
        PAX_NODISCARD const RenderPassChannel & getChannel(const std::string & name) const;
        PAX_NODISCARD const std::vector<RenderPassChannel> & getChannels() const;

        virtual void finalize();
    };
}

#endif //PAXENGINE3_RENDERPASS_H
