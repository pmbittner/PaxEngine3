//
// Created by Paul on 08.12.2017.
//

#include <core/rendering/SceneGraphGraphics.h>

namespace PAX {
    SceneGraphGraphics::SceneGraphGraphics() {}

    SceneGraph & SceneGraphGraphics::getSceneGraph() {
        return scenegraph;
    }

    void SceneGraphGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);
        scenegraph.render(renderOptions);
    }
}