//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_TEXTURE_H
#define PAXENGINE3_TEXTURE_H

namespace PAX {
    class Texture {
    public:
        enum class WrapMode {
            Repeat, MirrorRepeat, ClampToEdge, ClampToBorder
        };

    protected:
        int _width = 0;
        int _height = 0;
        WrapMode _wrapHorizontal = WrapMode::ClampToEdge;
        WrapMode _wrapVertical   = WrapMode::ClampToEdge;

    public:
        int getWidth();
        int getHeight();

        WrapMode getWrapModeHorizontal();
        WrapMode getWrapModeVertical();

        virtual void setWrapMode(WrapMode horizontal, WrapMode vertical);

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}
#endif //PAXENGINE3_TEXTURE_H
