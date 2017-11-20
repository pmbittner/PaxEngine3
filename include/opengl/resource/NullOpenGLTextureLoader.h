//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_OPENGLNULLTEXTURELOADER_H
#define PAXENGINE3_OPENGLNULLTEXTURELOADER_H

#include <core/rendering/resource/Texture.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLNullTextureLoader : public ResourceLoader<Texture, const char*> {
        public:
            OpenGLNullTextureLoader();
            ~OpenGLNullTextureLoader();

            bool free(Texture *res) override;
            bool canLoad(const char * path) override;
            Texture *load(const char * path) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLNULLTEXTURELOADER_H
