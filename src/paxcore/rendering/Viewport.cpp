//
// Created by Paul on 29.06.2017.
//

#include <paxcore/service/Services.h>
#include <paxcore/Engine.h>
#include <paxcore/rendering/Viewport.h>

namespace PAX {
    Viewport::Viewport() : _x(0), _y(0), _resizePolicy(ResizePolicy::Relative) {
        const std::shared_ptr<Window> & w = Services::GetWindowService().getWindow();
        _w = w->getResolution().x;
        _h = w->getResolution().y;

        w->OnResolutionChanged.add<Viewport, &Viewport::onWindowResolutionChanged>(this);
    }

    Viewport::Viewport(int x, int y, int w, int h, ResizePolicy resizePolicy) : _x(x), _y(y), _w(w), _h(h), _resizePolicy(resizePolicy) {
        if (_resizePolicy != ResizePolicy::Absolute) {
            Services::GetWindowService().getWindow()->OnResolutionChanged.add<Viewport, &Viewport::onWindowResolutionChanged>(this);
        }
    }

    Viewport::~Viewport() = default;

    void Viewport::onWindowResolutionChanged(ResolutionChangedEvent& e) {
        switch(_resizePolicy) {
            case ResizePolicy::Relative: {
                double xScale = static_cast<double>(e._newWidth)  / static_cast<double>(e._oldWidth);
                double yScale = static_cast<double>(e._newHeight) / static_cast<double>(e._oldHeight);

                setX(static_cast<int>(_x * xScale));
                setY(static_cast<int>(_y * yScale));
                setWidth(static_cast<int>(_w * xScale));
                setHeight(static_cast<int>(_h * yScale));

                break;
            }

            default: break;
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

    glm::ivec2 Viewport::getSize() const {
        return {getWidth(), getHeight()};
    }
}