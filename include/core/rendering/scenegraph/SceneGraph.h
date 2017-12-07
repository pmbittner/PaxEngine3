//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHNODE_H
#define PAXENGINE3_SCENEGRAPHNODE_H

#include <vector>
#include <utility/stdutils.h>

#include <core/rendering/interface/Renderable.h>

namespace PAX {
    /**
     *
     * @tparam ChildrensType Has to be a subtype of Renderable
     */
    template<class ChildrensType>
    class TypedSceneGraph : public Renderable {
    protected:
        std::vector<ChildrensType*> _children;

    public:
        TypedSceneGraph() {

        }

        virtual ~TypedSceneGraph() {
            _children.clear();
        }

        ChildrensType* operator<<=(ChildrensType* child) {
            _children.push_back(child);
            return child;
        }

        ChildrensType* addChild(ChildrensType* child) {
            _children.push_back(child);
            return child;
        }

        bool removeChild(ChildrensType* child) {
            return Util::removeFromVector(_children, child);
        }

        const std::vector<ChildrensType*>& getChildren() const {
            return _children;
        };

        bool isEmpty() {
            return _children.empty();
        }

        void render(RenderOptions &renderOptions) override {
            for (ChildrensType *child : _children)
                child->render(renderOptions);
        }
    };

    typedef TypedSceneGraph<Renderable> SceneGraph;
}

#endif //PAXENGINE3_SCENEGRAPHNODE_H
