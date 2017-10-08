//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_SDLOPENGLSETUP_H
#define PAXENGINE3_SDLOPENGLSETUP_H

#include "../SDLEngineSetup.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLEngineSetup : public SDLEngineSetup {
            public:
                virtual void registerServices() override;

                virtual Window *createWindow();
                virtual RenderFactory *createRenderFactory() override;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLSETUP_H
