//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Bla)
    PAX_TEST_PROPERTY_REFLECTION_SOURCE(PAX::Bla)

    PAX::Bla * Bla::createFromProvider(PAX::ContentProvider & provider) {
        return new Bla(provider.provide<int>(), provider.provide<std::string>());
    }

    void Bla::bla() {
        std::cout << "[PAX::Bla::bla](" << secretValue << ", " << secretMessage << ")" << std::endl;
    }
}