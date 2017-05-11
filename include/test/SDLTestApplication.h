//
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_SDLTESTAPPLICATION_H
#define PAXENGINE3_SDLTESTAPPLICATION_H

//
// Created by Paul on 17.04.2017.
//

#include <iostream>
#include <SDL2/SDL.h>

#include "../core/Engine.h"
#include "../sdl/utitlity/Path.h"

namespace SDL_TEST_APPLICATION {
    bool running = true;
    bool keyDown[1 << 30];

    void processEvent(SDL_Event *event);

    void update();

    void render();

// TEST values
    SDL_Renderer *renderer;

    float x, y;
    float speed = 5.0f;
    SDL_Texture *testSprite;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int run(int argc, char *argv[]) {
        SDL_Init(SDL_INIT_EVERYTHING);

        std::string windowTitle("TestWindow");
        int width = 800;
        int height = 600;

        SDL_Window *window;
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
            return 1;
        }

        // Test stuff
        std::string gregPath = getResourcePath() + "img/test/Gilgamesh.bmp";
        SDL_Surface *gregSurface = SDL_LoadBMP(gregPath.c_str());
        testSprite = SDL_CreateTextureFromSurface(renderer, gregSurface);
        SDL_free(gregSurface);

        SDL_QueryTexture(testSprite, NULL, NULL, &srcRect.w, &srcRect.h);
        destRect.w = srcRect.w;
        destRect.h = srcRect.h;

        // GAME LOOP

        SDL_Event event;

        while (running) {
            // Process Input
            while (SDL_PollEvent(&event)) {
                processEvent(&event);
            }

            update();
            render();

            SDL_Delay(25);
        }

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_DestroyTexture(testSprite);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
        return 0;
    }

    void processEvent(SDL_Event *event) {
        if (event->type == SDL_QUIT) {
            running = false;
        } else if (event->type == SDL_KEYDOWN) {
            std::cout << "Keydown " << event->key.keysym.sym << std::endl;
            keyDown[event->key.keysym.sym] = true;
        } else if (event->type == SDL_KEYUP) {
            keyDown[event->key.keysym.sym] = false;
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            int ix, iy;
            SDL_GetMouseState(&ix, &iy);
            x = ix - srcRect.w / 2;
            y = iy - srcRect.h / 2;
        }
    }

    void update() {
        if (keyDown[SDLK_w]) y -= speed;
        if (keyDown[SDLK_s]) y += speed;
        if (keyDown[SDLK_a]) x -= speed;
        if (keyDown[SDLK_d]) x += speed;

        destRect.x = (int) x;
        destRect.y = (int) y;
    }

    void render() {
        //First clear the renderer
        SDL_RenderClear(renderer);
        //Draw the texture
        SDL_RenderCopy(renderer, testSprite, &srcRect, &destRect);
        //Update the screen
        SDL_RenderPresent(renderer);
    }
}

#endif //PAXENGINE3_SDLTESTAPPLICATION_H
