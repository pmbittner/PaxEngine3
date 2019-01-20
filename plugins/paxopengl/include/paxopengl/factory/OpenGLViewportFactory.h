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
            std::shared_ptr<Viewport> create() override {
                return std::make_shared<OpenGLViewport>();
            }

            std::shared_ptr<Viewport> create(int x, int y, int w, int h, Viewport::ResizePolicy resizePolicy) override {
                return std::make_shared<OpenGLViewport>(x, y, w, h, resizePolicy);
            }
        };
    }
}
#endif //PAXENGINE3_OPENGLVIEWPORTFACTORY_H
