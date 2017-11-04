//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_TEXTURE_H
#define PAXENGINE3_TEXTURE_H

namespace PAX {
    class Texture {
    protected:
        int _width, _height;

    public:
        int getWidth();
        int getHeight();

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}
#endif //PAXENGINE3_TEXTURE_H
