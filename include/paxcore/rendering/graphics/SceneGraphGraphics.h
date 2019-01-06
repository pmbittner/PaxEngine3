//
// Created by Paul on 08.12.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHGRAPHICS_H
#define PAXENGINE3_SCENEGRAPHGRAPHICS_H

#include <paxcore/rendering/Graphics.h>

namespace PAX {
    class SceneGraphGraphics : public Graphics {
        PAX_PROPERTY(PAX::SceneGraphGraphics)
        PAX_PROPERTY_DERIVES(Graphics)
        PAX_PROPERTY_IS_SINGLE

    protected:
        SceneGraph _scenegraph;

    public:
        SceneGraphGraphics();

        SceneGraph& getSceneGraph();
        void render(RenderOptions &renderOptions) override final;
    };
}

#endif //PAXENGINE3_SCENEGRAPHGRAPHICS_H
