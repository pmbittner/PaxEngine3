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

    void Window::setResolution(const glm::ivec2 &resolution) {
        this->_resolution = resolution;
    }

    glm::ivec2 Window::getResolution() {
        return _resolution;
    }

    void Window::dispose() {}
}