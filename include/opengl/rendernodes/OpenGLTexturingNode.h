//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURENODE_H
#define PAXENGINE3_OPENGLTEXTURENODE_H

#include <core/rendering/scenegraph/nodes/TexturingNode.h>
#include <opengl/resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLTexturingNode : public TexturingNode {
        public:
            OpenGLTexturingNode(Texture *texture);
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURENODE_H
