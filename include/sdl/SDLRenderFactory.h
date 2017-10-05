//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_SDLRENDERFACTORY_H
#define PAXENGINE3_SDLRENDERFACTORY_H

#include "../core/rendering/RenderFactory.h"

namespace PAX {
    namespace SDL {
        class SDLRenderFactory : public RenderFactory {
        public:
            virtual SceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer) override;
            virtual SceneGraphGenerator* createSceneGraphGeneratorFor(WorldLayer *worldLayer) override;
        };
    }
}

#endif //PAXENGINE3_SDLRENDERFACTORY_H
