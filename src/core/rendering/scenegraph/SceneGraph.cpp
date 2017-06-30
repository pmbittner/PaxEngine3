//
// Created by Paul on 04.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraph.h"
#include "../../../../include/core/rendering/scenegraph/sort/RenderableSort.h"
#include "../../../../include/lib/easylogging++.h"
#include "../../../../include/utility/stdutils.h"

namespace PAX {
    SceneGraph::SceneGraph() {

    }

    SceneGraph::~SceneGraph() {
        for (SceneGraph* parent : _parents)
            parent->removeChild(this);

        _children.clear();

        LOG(WARNING) << "SceneGraph destructor is memory leaking! It does not delete children!";
    }

    void SceneGraph::render(RenderOptions &renderOptions) {
        _sorter.insertionSort(_children);

        for (Renderable *child : _children)
            child->render(renderOptions);
    }

    float SceneGraph::getZ() {
        return 0;
    }

    const std::vector<SceneGraph*>& SceneGraph::getParents() {
        return _parents;
    };

    void SceneGraph::addChild(SceneGraph *child) {
        child->_parents.push_back(this);
        _children.push_back(static_cast<Renderable*>(child));
    }

    bool SceneGraph::removeChild(SceneGraph *child) {
        if (Util::vectorContains(&_children, static_cast<Renderable*>(child))) {
            return Util::removeFromVector(&_children, static_cast<Renderable*>(child)) && Util::removeFromVector(&(child->_parents), this);
        }
    }

    void SceneGraph::addRenderable(Renderable *renderable) {
        _children.push_back(renderable);
    }

    bool SceneGraph::removeRenderable(Renderable *renderable) {
        return Util::removeFromVector(&_children, renderable);
    }

    bool SceneGraph::isEmpty() {
        return _children.empty();
    }

    void SceneGraph::prettyPrint() {

    }
}