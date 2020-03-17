//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SORTEDSCENEGRAPH_H
#define PAXENGINE3_SORTEDSCENEGRAPH_H

#include <paxcore/rendering/scenegraph/sort/GraphicsSort.h>
#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    template<typename Children, typename Sorter>
    class SortingNode : public TypedSceneGraph<Children> {
        Sorter sorter;

    public:
        explicit SortingNode(Sorter sorter = Sorter()) : TypedSceneGraph<Children>(), sorter(sorter) {}

        void render(RenderOptions &renderOptions) override {
            sorter.sort(TypedSceneGraph<Children>::_children);
            TypedSceneGraph<Children>::render(renderOptions);
        }
    };

    typedef SortingNode<Graphics, Sort::BackToFrontGraphicsSort> GraphicsSortingNode2D;
    typedef SortingNode<Graphics, Sort::FrontToBackGraphicsSort> GraphicsSortingNode3D;
}

#endif //PAXENGINE3_SORTEDSCENEGRAPH_H
