//
// Created by Paul on 02.07.2017.
//

#include <paxcore/io/Window.h>

namespace PAX {
    void Window::setFullscreen(bool fullscreen) {
        _fullscreen = fullscreen;
    }

    bool Window::isFullscreen() {
        return _fullscreen;
    }

    glm::ivec2 Window::getResolution() {
        return _resolution;
    }
}