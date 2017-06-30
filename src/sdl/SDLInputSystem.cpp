//
// Created by Paul on 11.05.2017.
//

#include <SDL_events.h>
#include "../../include/sdl/SDLInputSystem.h"
#include "../../include/core/io/Keyboard.h"
#include "../../include/core/Engine.h"

namespace PAX {
    void SDLInputSystem::initialize() {
        _mbPressed.mouse = &_mouse;
        _mbReleased.mouse = &_mouse;
    }

    void SDLInputSystem::update() {
        _keyboard.setKeyStates(SDL_GetKeyboardState(NULL));

        while (SDL_PollEvent(&_currentEvent)) {
            switch (_currentEvent.type) {
                case SDL_QUIT:
                    PAX::Engine::GetInstance()->stop();
                    break;
/*
                case SDL_KEYDOWN:
                    _keyboard.setKeyDown(_currentEvent.key.keysym.sym, true);
                    break;

                case SDL_KEYUP:
                    _keyboard.setKeyDown(_currentEvent.key.keysym.sym, false);
                    break;
//*/
                case SDL_MOUSEBUTTONDOWN:
                    _mbPressed.button = _currentEvent.button.button;
                    Engine::GetInstance()->getEventService()(_mbPressed);
                    break;

                case SDL_MOUSEBUTTONUP:
                    _mbPressed.button = _currentEvent.button.button;
                    Engine::GetInstance()->getEventService()(_mbReleased);
                    break;

                case SDL_MOUSEMOTION:
                    updateMouseLocation();
                    break;

                default: break;
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