//
// Created by paul on 01.06.17.
//

#include "../../../include/sdl/test/SDLSprite.h"
#include "../../../include/core/entity/Entity.h"
#include "../../../include/core/entity/Transform.h"
#include "../../../include/lib/easylogging++.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    SDLSprite::SDLSprite(SDL_Renderer *renderer, std::string path) : _renderer(renderer) {
        SDL_Surface *gregSurface = SDL_LoadBMP(path.c_str());
        _sprite = SDL_CreateTextureFromSurface(renderer, gregSurface);
        SDL_free(gregSurface);
        SDL_QueryTexture(_sprite, NULL, NULL, &_destRect.w, &_destRect.h);
        LOG(INFO) << "SDLSprite: Texture " << path << " loaded (" << _destRect.w << "/" << _destRect.h << ")" << std::endl;
    }

    void SDLSprite::render(RenderOptions &renderOptions) {
        Transform t = getOwner()->getTransform();
        _destRect.x = (int) (t.x() - _destRect.w / 2);
        _destRect.y = (int) (t.y() - _destRect.h / 2);
        SDL_RenderCopy(_renderer, _sprite,  NULL, &_destRect);
    }
}