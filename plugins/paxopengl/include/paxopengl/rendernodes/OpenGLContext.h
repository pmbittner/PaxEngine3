//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_OPENGLCONTEXT_H
#define PAXENGINE3_OPENGLCONTEXT_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    namespace OpenGL{
            class OpenGLContext : public SceneGraph {
            public:
                OpenGLContext();
                void initialize();
                virtual void render(RenderOptions &renderOptions) override;
            };
    }
}

#endif //PAXENGINE3_OPENGLCONTEXT_H
