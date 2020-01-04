//
// Created by Paul on 13.10.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTURELOADER_H
#define PAXENGINE3_OPENGLTEXTURELOADER_H

#ifdef PAX_WITH_FREEIMAGE

#include <paxcore/rendering/data/Texture.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class FreeImageOpenGLTextureLoader : public ResourceLoader<Texture, const char*> {
        public:
            FreeImageOpenGLTextureLoader();
            ~FreeImageOpenGLTextureLoader();

            PAX_NODISCARD bool canLoad(const char * path) const override;
            PAX_NODISCARD std::shared_ptr<Texture> load(const char * path) override;

            virtual std::shared_ptr<Texture> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters);
        };
    }
}
#endif // PAX_WITH_FREEIMAGE

#endif //PAXENGINE3_OPENGLTEXTURELOADER_H
