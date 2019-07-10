//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_TEXTURE_H
#define PAXENGINE3_TEXTURE_H

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    class Texture {
    public:
        enum class WrapMode {
            Repeat, MirrorRepeat, ClampToEdge, ClampToBorder
        };

        enum class FilterMode {
            Nearest, Linear
        };

        enum class PixelFormat {
            RGB, RGBA, BGR
        };

    protected:
        int width = 0;
        int height = 0;
        WrapMode wrapHorizontal = WrapMode::ClampToEdge;
        WrapMode wrapVertical   = WrapMode::ClampToEdge;
        FilterMode filterMode   = FilterMode::Linear;

    public:
        virtual ~Texture();

        int getWidth();
        int getHeight();
        glm::ivec2 getSize();

        WrapMode getWrapModeHorizontal();
        WrapMode getWrapModeVertical();

        FilterMode getFilterMode();

        virtual void setWrapMode(WrapMode horizontal, WrapMode vertical);
        virtual void setFilterMode(FilterMode mode);

        virtual void setPixels(void * data, PixelFormat dataPixelFormat);

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}
#endif //PAXENGINE3_TEXTURE_H
