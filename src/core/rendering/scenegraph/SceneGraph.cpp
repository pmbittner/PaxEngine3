//
// Created by Paul on 04.05.2017.
//

#include "../../../../include/core/rendering/scenegraph/SceneGraph.h"
#include "../../../../include/core/rendering/scenegraph/sort/RenderableSort.h"
#include "../../../../include/lib/easylogging++.h"
#include "../../../../include/utility/stdutils.h"

namespace PAX {
    SceneGraph::SceneGraph(float z) : _z(z) {

    }

    SceneGraph::~SceneGraph() {
        for (SceneGraph* parent : _parents)
            parent->removeChild(this);

        for (Renderable *renderable : _children)
            delete renderable;

        _children.clear();
    }

    void SceneGraph::render(RenderOptions &renderOptions) {
        for (Renderable *child : _children)
            child->render(renderOptions);
    }

    void SceneGraph::setZ(float z) {
        _z = z;
    }

    float SceneGraph::getZ() {
        return _z;
    }

    const std::vector<SceneGraph*>& SceneGraph::getParents() const {
        return _parents;
    };

    const std::vector<Renderable*>& SceneGraph::getChildren() const {
        return _children;
    };

    void SceneGraph::addChild(SceneGraph *child) {
        child->_parents.push_back(this);
        addRenderable(child);
    }

    bool SceneGraph::removeChild(SceneGraph *child) {
        if (Util::vectorContains<Renderable*>(&_children, child)) {
            return removeRenderable(child) && Util::removeFromVector(child->_parents, this);
        }
    }

    void SceneGraph::addRenderable(Renderable *renderable) {
        _children.push_back(renderable);
    }

    bool SceneGraph::removeRenderable(Renderable *renderable) {
        return Util::removeFromVector(_children, renderable);
    }

    bool SceneGraph::isEmpty() {
        return _children.empty();
    }
}