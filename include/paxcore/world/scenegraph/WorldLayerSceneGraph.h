//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_WORLDLAYERSCENEGRAPH_H
#define PAXENGINE3_WORLDLAYERSCENEGRAPH_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class WorldLayer;

    class WorldLayerSceneGraph : public SceneGraph {
        friend class WorldLayer;

        float _z;
        WorldLayer *worldLayer = nullptr;

    public:
        WorldLayerSceneGraph(float z);

        virtual void render(RenderOptions &renderOptions) override;

        void setZ(float z);
        float getZ();
    };
}

#endif //PAXENGINE3_WORLDLAYERSCENEGRAPH_H
