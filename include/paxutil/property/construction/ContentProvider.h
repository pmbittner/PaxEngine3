//
// Created by Bittner on 10/01/2019.
//

#ifndef PAXENGINE3_CONTENTPROVIDER_H
#define PAXENGINE3_CONTENTPROVIDER_H

#include <string>

namespace PAX {
    class ContentProvider {
    public:
        template<typename T>
        T provide() {
            return T();
        }
    };

    // This is just for testing
    template<>
    std::string ContentProvider::provide();
    template<>
    const std::string & ContentProvider::provide();
    template<>
    int ContentProvider::provide();
}

#endif //PAXENGINE3_CONTENTPROVIDER_H
