//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLSPRITE_H
#define PAXENGINE3_OPENGLSPRITE_H

#include <GL/glew.h>
#include "../core/rendering/Sprite.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLMesh;
        class OpenGLShader;
        class OpenGLTexture2D;

        class OpenGLSprite : public Sprite {
            static OpenGLMesh *QuadMesh;
            static OpenGLShader *SpriteShader;

            GLint ul_modelview, ul_projection, ul_texture;

        public:
            static void Initialize();
            OpenGLSprite(OpenGLTexture2D *texture);

            virtual void render(RenderOptions &options) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSPRITE_H
