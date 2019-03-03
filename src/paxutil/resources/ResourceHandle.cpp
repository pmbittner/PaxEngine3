//
// Created by Paul on 03.10.2017.
//

#include <paxutil/resources/ResourceHandle.h>

namespace PAX {
    ResourceHandle::ResourceHandle() {}

    ResourceHandle::~ResourceHandle() {
        delete _signature;
    }
}