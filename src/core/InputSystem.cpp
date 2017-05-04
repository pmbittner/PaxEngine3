//
// Created by Paul on 29.04.2017.
//

#include <SDL_events.h>
#include "../../include/core/InputSystem.h"
#include "../../include/core/io/Keyboard.h"
#include "../../include/core/Engine.h"

namespace PAX {
    void InputSystem::initialize() {

    }

    void InputSystem::update() {
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

    void InputSystem::updateMouseLocation() {
        SDL_GetMouseState(&_mouse.x, &_mouse.y);
    }

    Keyboard* InputSystem::getKeyboard() {
        return &_keyboard;
    }

    Mouse* InputSystem::getMouse() {
        return &_mouse;
    }
}