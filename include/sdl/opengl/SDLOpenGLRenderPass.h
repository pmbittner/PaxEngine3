//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_SDLOPENGLRENDERPASS_H
#define PAXENGINE3_SDLOPENGLRENDERPASS_H

#include "../../core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    class SDLOpenGLRenderPass : public SceneGraph {
    public:
        SDLOpenGLRenderPass();
        void initialize();
        virtual void render() override;
    };
}

#endif //PAXENGINE3_SDLOPENGLRENDERPASS_H
