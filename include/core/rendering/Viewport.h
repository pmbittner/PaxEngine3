//
// Created by Paul on 29.06.2017.
//

#ifndef PAXENGINE3_VIEWPORT_H
#define PAXENGINE3_VIEWPORT_H

namespace PAX {
    class Viewport {
    protected:
        int _x, _y, _w, _h;

    public:

        Viewport();
        Viewport(int x, int y, int w, int h);

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
