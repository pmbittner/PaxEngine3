//
// Created by Paul on 11.05.2017.
//

#include <SDL2/SDL_events.h>
#include "../../include/sdl/SDLInputSystem.h"
#include "../../include/core/Engine.h"

namespace PAX {
    namespace SDL {
        void SDLInputSystem::initialize() {
            _mbPressed.mouse = &_mouse;
            _mbReleased.mouse = &_mouse;
            _mWheel.mouse = &_mouse;
            _mMoved.mouse = &_mouse;
            _keyPressed.keyboard = &_keyboard;
            _keyReleased.keyboard = &_keyboard;
        }

        void SDLInputSystem::update() {
            _keyboard.setKeyStates(SDL_GetKeyboardState(nullptr));

            while (SDL_PollEvent(&_currentEvent)) {
                switch (_currentEvent.type) {
                    case SDL_QUIT: {
                        PAX::Engine::Instance().stop();
                        break;
                    }

                    case SDL_KEYDOWN: {
                        _keyPressed.button = static_cast<Key>(_currentEvent.key.keysym.scancode); // mapping is 1:1
                        _keyPressed.repeated = _currentEvent.key.repeat;
                        Services::GetEventService()(_keyPressed);
                        break;
                    }

                    case SDL_KEYUP: {
                        _keyReleased.button = static_cast<Key>(_currentEvent.key.keysym.scancode); // mapping is 1:1
                        Services::GetEventService()(_keyReleased);
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN: {
                        _mbPressed.button = static_cast<MouseButton>(_currentEvent.button.button); // mapping is 1:1
                        setMouseLocation(_mouse, _currentEvent.button.x, _currentEvent.button.y);
                        _mbPressed.clicks = _currentEvent.button.clicks;
                        Services::GetEventService()(_mbPressed);
                        break;
                    }

                    case SDL_MOUSEBUTTONUP: {
                        _mbReleased.button = static_cast<MouseButton>(_currentEvent.button.button); // mapping is 1:1
                        setMouseLocation(_mouse, _currentEvent.button.x, _currentEvent.button.y);
                        Services::GetEventService()(_mbReleased);
                        break;
                    }

                    case SDL_MOUSEWHEEL: {
                        char dir = _currentEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1 : 1;
                        _mWheel.ticksX = dir * _currentEvent.wheel.x;
                        _mWheel.ticksY = dir * _currentEvent.wheel.y;
                        Services::GetEventService()(_mWheel);
                    }

                    case SDL_MOUSEMOTION: {
                        _mMoved.oldX = _mouse.getX();
                        _mMoved.oldY = _mouse.getY();

                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        setMouseLocation(_mouse, x, y);

                        Services::GetEventService()(_mMoved);
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

        SDLKeyboard *SDLInputSystem::getKeyboard() {
            return &_keyboard;
        }

        Mouse *SDLInputSystem::getMouse() {
            return &_mouse;
        }
    }
}