//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_MOUSE_H
#define PAXENGINE3_MOUSE_H

namespace PAX {
    class Mouse {
    public:
        int x, y;
        int getX();
        int getY();
        bool isButtonDown();
    };
}

#endif //PAXENGINE3_MOUSE_H
