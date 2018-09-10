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
        class OpenGLViewportFactory : public Factory<Viewport> {
        public:
            virtual std::shared_ptr<Viewport> create() override {
                return std::make_shared<OpenGLViewport>();
            }
        };
    }
}
#endif //PAXENGINE3_OPENGLVIEWPORTFACTORY_H
