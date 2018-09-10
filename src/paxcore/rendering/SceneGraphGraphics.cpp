//
// Created by Paul on 08.12.2017.
//

#include <paxcore/rendering/graphics/SceneGraphGraphics.h>

namespace PAX {
    SceneGraphGraphics::SceneGraphGraphics() {}

    SceneGraph & SceneGraphGraphics::getSceneGraph() {
        return _scenegraph;
    }

    void SceneGraphGraphics::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);
        _scenegraph.render(renderOptions);
    }
}