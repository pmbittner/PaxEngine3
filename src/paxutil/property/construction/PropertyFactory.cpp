//
// Created by paul on 09.01.19.
//

#include <paxutil/property/construction/PropertyFactory.h>

namespace PAX {
    // This is just for testing
    template<>
    std::string ContentProvider::provide() {
        return "Morgenroete";
    }
    template<>
    int ContentProvider::provide() {
        return 24;
    }
}