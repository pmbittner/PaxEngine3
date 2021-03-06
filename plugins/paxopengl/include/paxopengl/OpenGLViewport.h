//
// Created by Paul on 29.06.2017.
//

#ifndef PAXENGINE3_OPENGLVIEWPORT_H
#define PAXENGINE3_OPENGLVIEWPORT_H

#include <paxcore/rendering/camera/Viewport.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLViewport : public Viewport {
        public:
            OpenGLViewport();

            OpenGLViewport(int x, int y, int w, int h, ResizePolicy resizePolicy);

            virtual void apply() override;
        };
    }
}

#endif //PAXENGINE3_OPENGLVIEWPORT_H
