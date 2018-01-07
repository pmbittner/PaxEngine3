//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_SDLIMAGEOPENGLSPRITESHEETLOADER_H
#define PAXENGINE3_SDLIMAGEOPENGLSPRITESHEETLOADER_H

#include <core/rendering/resource/SpriteSheet.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class SDLImageOpenGLSpriteSheetLoader : public ResourceLoader<SpriteSheet, Path, int, int> {
        public:
            SDLImageOpenGLSpriteSheetLoader();
            ~SDLImageOpenGLSpriteSheetLoader();

            bool free(SpriteSheet *res) override;
            bool canLoad(Path path, int cellWidth, int cellHeight) override;
            SpriteSheet *load(Path path, int cellWidth, int cellHeight) override;
        };
    }
}

#endif //PAXENGINE3_SDLIMAGEOPENGLSPRITESHEETLOADER_H
