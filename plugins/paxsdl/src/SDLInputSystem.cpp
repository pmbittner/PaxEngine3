//
// Created by Paul on 11.05.2017.
//

#include <SDL2/SDL_events.h>

#include <paxcore/Engine.h>

#include "paxsdl/SDLInputSystem.h"
#include "paxsdl/SDLWindow.h"

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

        void SDLInputSystem::terminate() {

        }

        void SDLInputSystem::update(UpdateOptions & options) {
            _keyboard.setKeyStates(SDL_GetKeyboardState(nullptr));

            int eventsProcessed = 0;
            while (SDL_PollEvent(&_currentEvent) && eventsProcessed < max_events_to_process_per_update) {
                switch (_currentEvent.type) {
                    case SDL_QUIT: {
                        PAX::Engine::Instance().stop();
                        break;
                    }

                    case SDL_KEYDOWN: {
                        _keyPressed.reuse();
                        _keyPressed.button = static_cast<Key>(_currentEvent.key.keysym.scancode); // mapping is 1:1
                        _keyPressed.repeated = _currentEvent.key.repeat;
                        Services::GetEventService()(_keyPressed);
                        break;
                    }

                    case SDL_KEYUP: {
                        _keyReleased.reuse();
                        _keyReleased.button = static_cast<Key>(_currentEvent.key.keysym.scancode); // mapping is 1:1
                        Services::GetEventService()(_keyReleased);
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN: {
                        _mbPressed.reuse();
                        _mbPressed.button = static_cast<MouseButton>(_currentEvent.button.button); // mapping is 1:1
                        setMouseScreenPosition(_mouse, _currentEvent.button.x, _currentEvent.button.y);
                        _mbPressed.clicks = _currentEvent.button.clicks;
                        Services::GetEventService()(_mbPressed);
                        break;
                    }

                    case SDL_MOUSEBUTTONUP: {
                        _mbReleased.reuse();
                        _mbReleased.button = static_cast<MouseButton>(_currentEvent.button.button); // mapping is 1:1
                        setMouseScreenPosition(_mouse, _currentEvent.button.x, _currentEvent.button.y);
                        Services::GetEventService()(_mbReleased);
                        break;
                    }

                    case SDL_MOUSEWHEEL: {
                        _mWheel.reuse();
                        int dir = _currentEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1 : 1;
                        _mWheel.ticksX = dir * _currentEvent.wheel.x;
                        _mWheel.ticksY = dir * _currentEvent.wheel.y;
                        Services::GetEventService()(_mWheel);
                    }

                    case SDL_MOUSEMOTION: {
                        _mMoved.reuse();
                        _mMoved.oldScreenPos = _mouse.getScreenPosition();

                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        setMouseScreenPosition(_mouse, x, y);

                        Services::GetEventService()(_mMoved);
                        break;
                    }

                    case SDL_WINDOWEVENT: {
                        switch (_currentEvent.window.event) {
                            case SDL_WINDOWEVENT_RESIZED: {
                                const std::shared_ptr<Window> window = Services::GetWindowService().getWindow();
                                glm::ivec2 newRes = {_currentEvent.window.data1, _currentEvent.window.data2};
                                ResolutionChangedEvent e(window->getResolution(), newRes);
                                setWindowResolution(*window, newRes);
                                window->OnResolutionChanged(e);
                                break;
                            }

                            case SDL_WINDOWEVENT_CLOSE: {
                                Engine::Instance().stop();
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

                ++eventsProcessed;
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