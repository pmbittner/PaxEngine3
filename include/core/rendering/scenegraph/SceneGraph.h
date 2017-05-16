//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPH_H
#define PAXENGINE3_SCENEGRAPH_H

#include <vector>
#include "SceneGraphBuilder.h"
#include "../Renderable.h"
#include "sort/RenderableSort.h"

namespace PAX {
    class SceneGraph : public Renderable {
        float _z;
        Sort::RenderableSort _sorter;
        std::vector<Renderable*> _children;

    public:
        SceneGraph();

        virtual void render() override;
        virtual float getZ() override;

        void setZ(float z);
    };
}

#endif //PAXENGINE3_SCENEGRAPH_H
