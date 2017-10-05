//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPH_H
#define PAXENGINE3_SCENEGRAPH_H

#include <vector>
#include "sort/RenderableSort.h"
#include "../RenderOptions.h"

namespace PAX {
    class SceneGraph : private Renderable {
    protected:
        float _z = 0;

        std::vector<SceneGraph*> _parents;
        std::vector<Renderable*> _children;

    public:
        SceneGraph(float z = 0);
        virtual ~SceneGraph();

        const std::vector<SceneGraph*>& getParents() const;
        const std::vector<Renderable*>& getChildren() const;

        /// Takes ownership of renderable
        void addRenderable(Renderable* renderable);
        bool removeRenderable(Renderable* renderable);

        /// Takes ownership of child
        void addChild(SceneGraph* child);
        bool removeChild(SceneGraph* child);

        bool isEmpty();

        virtual void render(RenderOptions &renderOptions) override;
        void setZ(float z);
        virtual float getZ() override;
    };
}

#endif //PAXENGINE3_SCENEGRAPH_H
