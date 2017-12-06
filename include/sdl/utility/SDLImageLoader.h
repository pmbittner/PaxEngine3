//
// Created by Paul on 14.04.2017.
//

#ifndef PAXENGINE3_SDLIMAGELOADER_H
#define PAXENGINE3_SDLIMAGELOADER_H

#include "SDL_image.h"
#include <iostream>

/**
 * DEPRECATED
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr){
        std::cout << "Could not load texture file " << file << SDL_GetError() << std::endl;
    }
    return texture;
}

#endif //PAXENGINE3_SDLIMAGELOADER_H
