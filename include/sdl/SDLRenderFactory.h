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
            virtual WorldLayerSceneGraph* createSceneGraphNodeFor(WorldLayer *worldLayer, float z) override;
            virtual SceneGraphGenerator* createDefaultSceneGraphGenerator() override;
        };
    }
}

#endif //PAXENGINE3_SDLRENDERFACTORY_H
