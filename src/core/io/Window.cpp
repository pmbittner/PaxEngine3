//
// Created by Paul on 02.07.2017.
//

#include "../../../include/core/io/Window.h"

namespace PAX {
    void Window::setFullscreen(bool fullscreen) {
        _fullscreen = fullscreen;
    }

    bool Window::isFullscreen() {
        return _fullscreen;
    }
}