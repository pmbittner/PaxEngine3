//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_SDLSPRITE_H
#define PAXENGINE3_SDLSPRITE_H

#include "../../core/rendering/Graphics.h"

namespace PAX {
    class SDLSprite  : public Graphics {
        static SceneGraphBuildingRule* sceneGraphBuildingRule;

    public:
        virtual SceneGraphBuildingRule* getSceneGraphBuildingRule() override;
        virtual void render() override;
    };
}

#endif //PAXENGINE3_SDLSPRITE_H
