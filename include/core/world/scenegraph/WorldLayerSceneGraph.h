//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_WORLDLAYERSCENEGRAPH_H
#define PAXENGINE3_WORLDLAYERSCENEGRAPH_H

#include <core/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class WorldLayerSceneGraph : public SceneGraph {
        float _z;

    public:
        WorldLayerSceneGraph(float z);

        void setZ(float z);
        float getZ();
    };
}

#endif //PAXENGINE3_WORLDLAYERSCENEGRAPH_H
