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
        float z;

    public:
        void render(RenderOptions &renderOptions) override;
        PAX_NODISCARD World* getWorld() const;
        PAX_NODISCARD float getZ() const;

        PAX_NODISCARD bool operator<(const WorldSceneGraph& other) const;
    };
}

#endif //PAXENGINE3_WORLDSCENEGRAPH_H
