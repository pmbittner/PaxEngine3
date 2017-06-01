//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_SDLSPRITE_H
#define PAXENGINE3_SDLSPRITE_H

#include <string>
#include <SDL_render.h>
#include "../../core/rendering/Graphics.h"

namespace PAX {
    class SDLSprite : public Graphics {
        static SceneGraphBuildingRule* sceneGraphBuildingRule;
        SDL_Texture *_sprite = nullptr;
        SDL_Renderer *_renderer = nullptr;
        SDL_Rect _destRect;

    public:
        SDLSprite(SDL_Renderer *renderer, std::string path);

        virtual SceneGraphBuildingRule* getSceneGraphBuildingRule() override;
        virtual void render() override;
    };
}

#endif //PAXENGINE3_SDLSPRITE_H
