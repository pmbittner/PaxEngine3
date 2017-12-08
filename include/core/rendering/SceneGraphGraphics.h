//
// Created by Paul on 08.12.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHGRAPHICS_H
#define PAXENGINE3_SCENEGRAPHGRAPHICS_H

#include "Graphics.h"

namespace PAX {
    class SceneGraphGraphics : public Graphics {
    protected:
        SceneGraph scenegraph;

    public:
        SceneGraphGraphics();
        SceneGraph& getSceneGraph();

        void render(RenderOptions &renderOptions) override final;
    };
}

#endif //PAXENGINE3_SCENEGRAPHGRAPHICS_H
