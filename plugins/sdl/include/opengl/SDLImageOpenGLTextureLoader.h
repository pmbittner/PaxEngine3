//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H
#define PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H

#include <core/rendering/data/Texture.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class SDLImageOpenGLTextureLoader : public ResourceLoader<Texture, Path> {
        public:
            SDLImageOpenGLTextureLoader();
            ~SDLImageOpenGLTextureLoader();

            bool canLoad(Path path) override;
            std::shared_ptr<Texture> load(Path path) override;
        };
    }
}

#endif //PAXENGINE3_SDLIMAGEOPENGLTEXTURELOADER_H
