//
// Created by paul on 01.06.17.
//

#include "../../../include/sdl/test/SDLSprite.h"
#include "../../../include/core/rendering/scenegraph/rule/ListSceneGraphBuildingRule.h"

namespace PAX {
    SceneGraphBuildingRule *SDLSprite::sceneGraphBuildingRule = new ListSceneGraphBuildingRule();

    SceneGraphBuildingRule * SDLSprite::getSceneGraphBuildingRule() {
        return sceneGraphBuildingRule;
    }

    void SDLSprite::render() {

    }
}