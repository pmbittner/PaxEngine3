//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_TEXTURE_H
#define PAXENGINE3_TEXTURE_H

namespace PAX {
    class Texture {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}
#endif //PAXENGINE3_TEXTURE_H
