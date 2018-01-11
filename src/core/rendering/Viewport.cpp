//
// Created by Paul on 29.06.2017.
//

#include <core/service/Services.h>
#include <core/Engine.h>
#include "../../../include/core/rendering/Viewport.h"

namespace PAX {
    Viewport::Viewport() : _x(0), _y(0), _resizePolicy(ResizePolicy::Relative) {
        Window *w = Engine::Instance().getWindow();
        _w = w->getResolution().x;
        _h = w->getResolution().y;

        w->OnResolutionChanged.add<Viewport, &Viewport::onWindowResolutionChanged>(this);
    }

    Viewport::Viewport(int x, int y, int w, int h, ResizePolicy resizePolicy) : _x(x), _y(y), _w(w), _h(h), _resizePolicy(resizePolicy) {
        if (_resizePolicy != ResizePolicy::Absolute) {
            Engine::Instance().getWindow()->OnResolutionChanged.add<Viewport, &Viewport::onWindowResolutionChanged>(this);
        }
    }

    void Viewport::onWindowResolutionChanged(ResolutionChangedEvent& e) {
        switch(_resizePolicy) {
            case ResizePolicy::Relative: {
                double xScale = static_cast<double>(e._newWidth)  / static_cast<double>(e._oldWidth);
                double yScale = static_cast<double>(e._newHeight) / static_cast<double>(e._oldHeight);

                _x *= xScale;
                _w *= xScale;
                _y *= yScale;
                _h *= yScale;

                break;
            }
        }
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