//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_RENDERPASSCHANNEL_H
#define PAXENGINE3_RENDERPASSCHANNEL_H

#include <memory>
#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    class RenderPass;

    class RenderPassChannel {
        friend RenderPass;

    public:
        static constexpr const char* Colour = "Colour";
        //static constexpr const char* NameDepth = "Depth";

    private:
        std::shared_ptr<Texture> texture = nullptr;
        Texture::PixelFormat pixelFormat;
        std::string name;

        void initialize(RenderPass * renderPass);

    public:
        RenderPassChannel(const std::string & name, Texture::PixelFormat format);
        ~RenderPassChannel();

        PAX_NODISCARD const std::shared_ptr<Texture> & getTexture() const;
        PAX_NODISCARD const std::string & getName() const;
    };
}

#endif //PAXENGINE3_RENDERPASSCHANNEL_H
