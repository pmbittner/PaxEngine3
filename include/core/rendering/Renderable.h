//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_RENDERABLE_H
#define PAXENGINE3_RENDERABLE_H

namespace PAX {
    class Renderable {
    public:
        virtual void render() = 0;
        virtual float getZ() = 0;
    };
}

#endif //PAXENGINE3_RENDERABLE_H
