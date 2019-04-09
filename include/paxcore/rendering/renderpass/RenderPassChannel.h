//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_RENDERPASSCHANNEL_H
#define PAXENGINE3_RENDERPASSCHANNEL_H

#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    class RenderPass;

    class RenderPassChannel {
        friend class RenderPass;

    public:
        enum class Format {
            RGBA,
            Depth
        };

        enum class ValueType {
            Float,
            Depth = Float
        };

    private:
        RenderPass * renderPass = nullptr;
        int id = 0;
        Format format;
        ValueType valueType;

    protected:
        virtual void attached(RenderPass * renderPass);
        virtual void detached(RenderPass * renderPass);

    public:
        RenderPassChannel(Format format, ValueType valueType);
        virtual ~RenderPassChannel();

        RenderPass * getRenderPass() const;
        int getID() const;
        Format getFormat() const;
        ValueType getValueType() const;

        virtual const Texture & getTexture() const = 0;
    };
}

#endif //PAXENGINE3_RENDERPASSCHANNEL_H
