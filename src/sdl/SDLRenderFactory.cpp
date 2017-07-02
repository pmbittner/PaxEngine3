//
// Created by Paul on 02.07.2017.
//

#include "../../include/sdl/SDLRenderFactory.h"
#include "../../include/core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    namespace SDL {
        SceneGraph * SDLRenderFactory::createWorldLayerSceneGraphNode() {
            return new SceneGraph();
        }
    }
}