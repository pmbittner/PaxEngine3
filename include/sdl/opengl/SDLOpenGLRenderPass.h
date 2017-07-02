//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_SDLOPENGLRENDERPASS_H
#define PAXENGINE3_SDLOPENGLRENDERPASS_H

#include "../../core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLRenderPass : public SceneGraph {
            public:
                SDLOpenGLRenderPass();

                void initialize();
                virtual void render(RenderOptions &renderOptions) override;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLRENDERPASS_H
