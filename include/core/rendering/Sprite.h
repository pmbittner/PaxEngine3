//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SPRITE_H
#define PAXENGINE3_SPRITE_H

#include "Graphics.h"
#include "resource/Texture.h"
#include "resource/Mesh.h"
#include "resource/Shader.h"

namespace PAX {
    class Sprite : public Graphics {
        Shader *_shader;
        Texture *_texture;
        Mesh *_mesh;

    public:
        Sprite(Texture *texture, Mesh *mesh, Shader *shader);
        virtual void render(RenderOptions &options) override;

        Shader *getShader() const;
        Texture *getTexture() const;
        Mesh *getMesh() const;
    };
}

#endif //PAXENGINE3_SPRITE_H
