//
// Created by Paul on 11.05.2017.
//

#include <SDL_events.h>
#include "../../include/sdl/SDLInputSystem.h"
#include "../../include/core/Engine.h"

namespace PAX {
    namespace SDL {
        void SDLInputSystem::initialize() {
            _mbPressed.mouse = &_mouse;
            _mbReleased.mouse = &_mouse;
        }

        void SDLInputSystem::update() {
            _keyboard.setKeyStates(SDL_GetKeyboardState(NULL));

            while (SDL_PollEvent(&_currentEvent)) {
                switch (_currentEvent.type) {
                    case SDL_QUIT: {
                        PAX::Engine::Instance().stop();
                        break;
                    }

                    case SDL_KEYDOWN: {
                        //_keyboard.setKeyDown(_currentEvent.key.keysym.sym, true);
                        if (_currentEvent.key.keysym.sym == SDLK_ESCAPE)
                            PAX::Engine::Instance().stop();
                        break;
                    }

                    case SDL_KEYUP: {
                        //_keyboard.setKeyDown(_currentEvent.key.keysym.sym, false);
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN: {
                        _mbPressed.button = _currentEvent.button.button;
                        Services::GetEventService()(_mbPressed);
                        break;
                    }

                    case SDL_MOUSEBUTTONUP: {
                        _mbPressed.button = _currentEvent.button.button;
                        Services::GetEventService()(_mbReleased);
                        break;
                    }

                    case SDL_MOUSEMOTION: {
                        updateMouseLocation();
                        break;
                    }

                    case SDL_WINDOWEVENT: {
                        switch (_currentEvent.window.event) {
                            case SDL_WINDOWEVENT_RESIZED: {
                                Window *window = Engine::Instance().getWindow();
                                ResolutionChangedEvent e(window->getResolution(), glm::vec2(_currentEvent.window.data1,
                                                                                            _currentEvent.window.data2));
                                window->OnResolutionChanged(e);
                                break;
                            }

                            default:
                                break;

                        }
                        break;
                    }

                    default:
                        break;
                }
            }
        }

        void SDLInputSystem::updateMouseLocation() {
            SDL_GetMouseState(&_mouse.x, &_mouse.y);
        }

        Keyboard *SDLInputSystem::getKeyboard() {
            return &_keyboard;
        }

        Mouse *SDLInputSystem::getMouse() {
            return &_mouse;
        }
    }
}