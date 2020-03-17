//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_WORLDSCENEGRAPH_H
#define PAXENGINE3_WORLDSCENEGRAPH_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class World;

    class WorldSceneGraph : public SceneGraph {
        friend class World;
        World * world = nullptr;

    public:
        virtual void render(RenderOptions &renderOptions) override;
        World* getWorld();
    };
}

#endif //PAXENGINE3_WORLDSCENEGRAPH_H
