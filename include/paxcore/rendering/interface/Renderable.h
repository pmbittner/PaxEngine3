//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_RENDERABLE_H
#define PAXENGINE3_RENDERABLE_H

#include "../RenderOptions.h"

namespace PAX {
    class Renderable {
    public:
        virtual ~Renderable() = 0;
        virtual void render(RenderOptions &renderOptions) = 0;
    };
}

#endif //PAXENGINE3_RENDERABLE_H
