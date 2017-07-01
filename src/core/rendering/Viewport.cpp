//
// Created by Paul on 29.06.2017.
//

#include "../../../include/core/rendering/Viewport.h"

namespace PAX {
    Viewport::Viewport() : Viewport(0, 0, 800, 600) {

    }

    Viewport::Viewport(int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h) {

    }

    int Viewport::getX() const {
        return _x;
    }

    void Viewport::setX(int x) {
        Viewport::_x = x;
    }

    int Viewport::getY() const {
        return _y;
    }

    void Viewport::setY(int y) {
        Viewport::_y = y;
    }

    int Viewport::getWidth() const {
        return _w;
    }

    void Viewport::setWidth(int w) {
        WidthChanged(_w, w);
        Viewport::_w = w;
    }

    int Viewport::getHeight() const {
        return _h;
    }

    void Viewport::setHeight(int h) {
        HeightChanged(_h, h);
        Viewport::_h = h;
    }
}