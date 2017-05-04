//
// Created by Paul on 29.04.2017.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <sstream>

#include "../../include/utility/Path.h"
#include "../../include/core/Engine.h"

#include "../../include/test/SDLTestApplication2.h"
#include "../../include/lib/easylogging++.h"

#include "../../include/utility/OSDefines.h"

namespace SDL_TEST_APPLICATION2 {
    SDL_Renderer *renderer;
    SDL_Window *window;

    float x, y;
    float speed = 5.0f;
    SDL_Texture *testSprite;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    SDL_Texture* message;
    SDL_Rect message_rect;

    TTF_Font* font;
    SDL_Color fontColor = {255, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

        void SDLTestApplication2GameSystem::initialize() {
#ifdef PAX_OS_LINUX
            LOG(INFO) << "INIT SDL2TestApplication2 on Linux";
#endif
#ifdef PAX_OS_WIN
            LOG(INFO) << "INIT SDL2TestApplication2 on Windows";
#endif
#ifdef PAX_OS_ANDROID
            LOG(INFO) << "INIT SDL2TestApplication2 on Android";
#endif
            SDL_Init(SDL_INIT_EVERYTHING);

            std::string windowTitle("TestWindow");
            int width = 800;
            int height = 600;

            window = SDL_CreateWindow(windowTitle.c_str(),
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      width,
                                      height,
                                      SDL_WINDOW_RESIZABLE);

            if (window == NULL) {
                std::cout << "Window could not be created: " << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) {
                SDL_DestroyWindow(window);
                std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
                SDL_Quit();
                return;
            }

            // Test stuff
            std::string gregPath = getResourcePath() + "img/test/Gilgamesh.bmp";
            SDL_Surface *gregSurface = SDL_LoadBMP(gregPath.c_str());
            testSprite = SDL_CreateTextureFromSurface(renderer, gregSurface);
            SDL_free(gregSurface);

            SDL_QueryTexture(testSprite, NULL, NULL, &srcRect.w, &srcRect.h);
            destRect.w = srcRect.w;
            destRect.h = srcRect.h;

            std::string fontPath = getResourcePath() + "font/Pixeled.ttf";
            TTF_Init();
            font = TTF_OpenFont(fontPath.c_str(), 16); //this opens a font style and sets a size
            if (font);else {
                std::cout << SDL_GetError() << std::endl;
                std::cout << std::endl << gregPath << std::endl;
                std::cout << fontPath << std::endl;
            }

            //create a rect
            message_rect.x = 10;  //controls the rect's x coordinate
            message_rect.y = 10; // controls the rect's y coordinte
            message_rect.w = 70; // controls the width of the rect
            message_rect.h = 100; // controls the height of the rect
        }

        void SDLTestApplication2GameSystem::update() {
            PAX::Keyboard *keyboard = PAX::Engine::getInstance()->getInputSystem()->getKeyboard();
            PAX::Mouse *mouse = PAX::Engine::getInstance()->getInputSystem()->getMouse();

            if (keyboard->isKeyDown(SDLK_w)) y -= speed;
            if (keyboard->isKeyDown(SDLK_s)) y += speed;
            if (keyboard->isKeyDown(SDLK_a)) x -= speed;
            if (keyboard->isKeyDown(SDLK_d)) x += speed;

            x = mouse->getX() - srcRect.w / 2;
            y = mouse->getY() - srcRect.h / 2;
            destRect.x = (int) x;
            destRect.y = (int) y;

            if (message)
                SDL_DestroyTexture(message);

            std::ostringstream strs;
            strs << (int)PAX::Engine::getInstance()->getFPS();

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, strs.str().c_str(), fontColor); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
            message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
            SDL_free(surfaceMessage);
        }

    SDLTestApplication2GameSystem::~SDLTestApplication2GameSystem() {
            SDL_DestroyWindow(window);
            window = nullptr;

            SDL_DestroyTexture(message);
            SDL_DestroyTexture(testSprite);
            SDL_DestroyRenderer(renderer);

            TTF_CloseFont(font);
            TTF_Quit();

            SDL_Quit();
        }

    void render() {
        //First clear the renderer
        SDL_RenderClear(renderer);
        //Draw the texture
        SDL_RenderCopy(renderer, message, NULL, &message_rect);
        SDL_RenderCopy(renderer, testSprite, &srcRect, &destRect);
        //Update the screen
        SDL_RenderPresent(renderer);
    }
}