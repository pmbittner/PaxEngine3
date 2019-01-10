//
// Created by paul on 09.01.19.
//

#include <paxutil/property/construction/ContentProvider.h>

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
    template<>
    const std::string & ContentProvider::provide() {
        static std::string str = "const Morgenroete";
        return str;
    }
}