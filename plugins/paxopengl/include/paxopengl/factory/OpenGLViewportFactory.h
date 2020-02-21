//
// Created by Paul on 20.08.2018.
//

#ifndef PAXENGINE3_OPENGLVIEWPORTFACTORY_H
#define PAXENGINE3_OPENGLVIEWPORTFACTORY_H

#include "../OpenGLViewport.h"
#include <paxcore/rendering/factory/ViewportFactory.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLViewportFactory : public ViewportFactory {
        public:
            Viewport * create() override {
                return new OpenGLViewport();
            }

            Viewport * create(int x, int y, int w, int h, Viewport::ResizePolicy resizePolicy) override {
                return new OpenGLViewport(x, y, w, h, resizePolicy);
            }
        };
    }
}
#endif //PAXENGINE3_OPENGLVIEWPORTFACTORY_H
