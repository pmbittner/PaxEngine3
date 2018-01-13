//
// Created by Paul on 08.12.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHGRAPHICS_H
#define PAXENGINE3_SCENEGRAPHGRAPHICS_H

#include "core/rendering/Graphics.h"

namespace PAX {
    PAX_EntityComponentSub(SceneGraphGraphics, Graphics)
    class SceneGraphGraphics : public Graphics {
    protected:
        SceneGraph _scenegraph;

    public:
        SceneGraphGraphics();

        SceneGraph& getSceneGraph();
        void render(RenderOptions &renderOptions) override final;
    };
}

#endif //PAXENGINE3_SCENEGRAPHGRAPHICS_H
