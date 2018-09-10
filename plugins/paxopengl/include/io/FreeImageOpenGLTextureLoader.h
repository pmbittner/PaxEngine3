//
// Created by Paul on 13.10.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURELOADER_H
#define PAXENGINE3_OPENGLTEXTURELOADER_H

#include <paxcore/rendering/data/Texture.h>
#include <paxcore/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class FreeImageOpenGLTextureLoader : public ResourceLoader<Texture, const char*> {
        public:
            FreeImageOpenGLTextureLoader();
            ~FreeImageOpenGLTextureLoader();

            bool canLoad(const char * path) override;
            std::shared_ptr<Texture> load(const char * path) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTURELOADER_H
