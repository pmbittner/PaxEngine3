//
// Created by Paul on 29.06.2017.
//

#ifndef PAXENGINE3_VIEWPORT_H
#define PAXENGINE3_VIEWPORT_H

#include <paxcore/io/event/ResolutionChangedEvent.h>
#include "../event/EventHandler.h"

namespace PAX {
    class Viewport {
    public:
        enum class ResizePolicy {
            Absolute,
            Relative
        };

    protected:
        int _x, _y, _w, _h;
        ResizePolicy _resizePolicy = ResizePolicy::Absolute;

        void onWindowResolutionChanged(ResolutionChangedEvent& e);

    public:
        /**
         * first = old value
         * second = new value
         */
        EventHandler<int, int> WidthChanged, HeightChanged;

        Viewport();
        Viewport(int x, int y, int w, int h, ResizePolicy resizePolicy = ResizePolicy::Absolute);

        virtual void apply() = 0;

        int getX() const;
        void setX(int x);
        int getY() const;
        void setY(int y);
        int getWidth() const;
        void setWidth(int w);
        int getHeight() const;
        void setHeight(int h);
    };
}

#endif //PAXENGINE3_VIEWPORT_H
