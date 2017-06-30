//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLSPRITE_H
#define PAXENGINE3_OPENGLSPRITE_H

#include "../core/rendering/Sprite.h"
#include "resource/OpenGLTexture2D.h"
#include "resource/OpenGLMesh.h"
#include "resource/OpenGLShader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLSprite : public Sprite {
            GLint ul_modelview, ul_projection, ul_texture;

        public:
            OpenGLSprite(OpenGLTexture2D *texture, OpenGLMesh *mesh, OpenGLShader *shader);
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSPRITE_H
