//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_WINDOWFACTORY_H
#define PAXENGINE3_WINDOWFACTORY_H

#include <memory>
#include "Window.h"

namespace PAX {
    class WindowFactory {
    public:
        virtual std::shared_ptr<Window> create(const char* title, int resX, int resY) = 0;
    };
}

#endif //PAXENGINE3_WINDOWFACTORY_H
