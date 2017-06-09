//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_SDLTESTAPPLICATION2_H
#define PAXENGINE3_SDLTESTAPPLICATION2_H

//
// Created by Paul on 17.04.2017.
//
//#define PAX_DEMO_USE_TTF

#include <SDL2/SDL.h>

#ifdef PAX_DEMO_USE_TTF
#include <SDL2/SDL_ttf.h>
#endif

#include "../core/system/EntityComponentSystem.h"

namespace SDL_TEST_APPLICATION2 {
// TEST values
    extern SDL_Renderer *renderer;
    extern SDL_Window *window;

    extern float x, y;
    extern float speed;
    extern SDL_Texture *testSprite;
    extern SDL_Rect srcRect;
    extern SDL_Rect destRect;

    extern SDL_Texture* message;
    extern SDL_Rect message_rect;
#ifdef PAX_DEMO_USE_TTF
    extern TTF_Font* font;
    extern SDL_Color fontColor;  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
#endif

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    class SDLTestApplication2GameSystem : public PAX::EngineSystem {


        virtual void initialize() override;
        virtual void update() override;

        ~SDLTestApplication2GameSystem();
    };

    void render();
}

#endif //PAXENGINE3_SDLTESTAPPLICATION2_H
