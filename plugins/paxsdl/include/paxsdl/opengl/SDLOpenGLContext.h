//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_SDLOPENGLCONTEXT_H
#define PAXENGINE3_SDLOPENGLCONTEXT_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLContext : public SceneGraph {
            public:
                SDLOpenGLContext();

                void initialize();
                void render(RenderOptions &renderOptions) override;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLCONTEXT_H
