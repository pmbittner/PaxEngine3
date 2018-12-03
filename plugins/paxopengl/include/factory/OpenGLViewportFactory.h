//
// Created by Paul on 20.08.2018.
//

#ifndef PAXENGINE3_OPENGLVIEWPORTFACTORY_H
#define PAXENGINE3_OPENGLVIEWPORTFACTORY_H

#include <paxcore/service/Factory.h>
#include <paxcore/rendering/Viewport.h>
#include <paxopengl/include/OpenGLViewport.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLViewportFactory : public Factory<Viewport>, public Factory<Viewport, int, int, int, int, Viewport::ResizePolicy> {
        public:
            virtual std::shared_ptr<Viewport> create() override {
                return std::make_shared<OpenGLViewport>();
            }

            virtual std::shared_ptr<Viewport> create(int x, int y, int w, int h, Viewport::ResizePolicy resizePolicy) override {
                return std::make_shared<OpenGLViewport>(x, y, w, h, resizePolicy);
            }
        };
    }
}
#endif //PAXENGINE3_OPENGLVIEWPORTFACTORY_H
