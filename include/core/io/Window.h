//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_WINDOW_H
#define PAXENGINE3_WINDOW_H

#include <string>

namespace PAX {
    class Window {
    public:
        virtual bool create(std::string title, int width, int height) = 0;
    };
}

#endif //PAXENGINE3_WINDOW_H
