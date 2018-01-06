//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H
#define PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H

#include <core/rendering/resource/Texture.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class SDLImageOpenGLTextureLoader : public ResourceLoader<Texture, Path> {
        public:
            SDLImageOpenGLTextureLoader();
            ~SDLImageOpenGLTextureLoader();

            bool free(Texture *res) override;
            bool canLoad(Path path) override;
            Texture *load(Path path) override;
        };
    }
}

#endif //PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H
