//
// Created by Paul on 13.10.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURELOADER_H
#define PAXENGINE3_OPENGLTEXTURELOADER_H

#include <core/rendering/resource/Texture.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class FreeImageOpenGLTextureLoader : public ResourceLoader<Texture, const char*> {
        public:
            FreeImageOpenGLTextureLoader();
            ~FreeImageOpenGLTextureLoader();

            bool free(Texture *res) override;
            bool canLoad(const char * path) override;
            Texture *load(const char * path) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURELOADER_H
