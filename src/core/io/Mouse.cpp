//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/io/Mouse.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    int Mouse::getX() {
        return x;
    }

    int Mouse::getY() {
        return y;
    }

    bool Mouse::isButtonDown(int button) {
        LOG(WARNING) << "Mouse::isButtonDown not implemented";
        return false;
    }
}