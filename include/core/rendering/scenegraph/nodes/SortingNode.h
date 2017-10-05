//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SORTEDSCENEGRAPH_H
#define PAXENGINE3_SORTEDSCENEGRAPH_H

#include <core/rendering/scenegraph/sort/RenderableSort.h>
#include "core/rendering/scenegraph/SceneGraph.h"

namespace PAX {
    class SortingNode : public SceneGraph {
        Sort::RenderableSort _sorter;

    public:
        SortingNode();
        virtual ~SortingNode();

        virtual void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_SORTEDSCENEGRAPH_H
