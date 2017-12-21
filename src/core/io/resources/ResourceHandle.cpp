//
// Created by Paul on 03.10.2017.
//

#include <core/io/resources/ResourceHandle.h>

namespace PAX {
    ResourceHandle::ResourceHandle() {}

    ResourceHandle::~ResourceHandle() {
        delete _signature;
    }
}