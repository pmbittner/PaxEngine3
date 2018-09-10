//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_OPENGLNULLTEXTURELOADER_H
#define PAXENGINE3_OPENGLNULLTEXTURELOADER_H

#include <paxcore/rendering/data/Texture.h>
#include <paxcore/io/resources/ResourceLoader.h>
#include "OpenGLTexture2D.h"

namespace PAX {
    namespace OpenGL {
        class NullOpenGLTextureLoader : public ResourceLoader<Texture, const char*> {
        private:
            // Cache texture here, so that it will never be deleted.
            std::shared_ptr<OpenGLTexture2D> _texture = nullptr;

        public:
            NullOpenGLTextureLoader();
            ~NullOpenGLTextureLoader();

            bool canLoad(const char * path) override;
            std::shared_ptr<Texture> load(const char * path) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLNULLTEXTURELOADER_H
