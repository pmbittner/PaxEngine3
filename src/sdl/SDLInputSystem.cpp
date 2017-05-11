//
// Created by Paul on 11.05.2017.
//

#include <SDL_events.h>
#include "../../include/sdl/SDLInputSystem.h"
#include "../../include/core/io/Keyboard.h"
#include "../../include/core/Engine.h"

namespace PAX {
    void SDLInputSystem::initialize() {

    }

    void SDLInputSystem::update() {
        while (SDL_PollEvent(&_currentEvent)) {
            if (_currentEvent.type == SDL_QUIT) {
                PAX::Engine::getInstance()->stop();
            } else if (_currentEvent.type == SDL_KEYDOWN) {
                _keyboard.keyDown[_currentEvent.key.keysym.sym] = true;
            } else if (_currentEvent.type == SDL_KEYUP) {
                _keyboard.keyDown[_currentEvent.key.keysym.sym] = false;
            } else if (_currentEvent.type == SDL_MOUSEBUTTONDOWN) {

            } else if (_currentEvent.type == SDL_MOUSEMOTION) {
                updateMouseLocation();
            }
        }
    }

    void SDLInputSystem::updateMouseLocation() {
        SDL_GetMouseState(&_mouse.x, &_mouse.y);
    }

    Keyboard* SDLInputSystem::getKeyboard() {
        return &_keyboard;
    }

    Mouse* SDLInputSystem::getMouse() {
        return &_mouse;
    }
}