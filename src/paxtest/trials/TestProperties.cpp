//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Bla)
    PAX_TEST_PROPERTY_REFLECTION_CONSTRUCTOR_SOURCE(PAX::Bla, int, const std::string&)

    PAX_TEST_PROPERTY_CONSTRUCTOR_SOURCE(PAX::Bla, (int x, const std::string & s), (x, s))
    PAX_TEST_PROPERTY_CONSTRUCTOR_SOURCE(PAX::Bla, (int x), (x))
    PAX_TEST_PROPERTY_DEFAULT_CONSTRUCTOR_SOURCE(PAX::Bla)

    void Bla::bla() {
        std::cout << "[PAX::Bla::bla](" << secretValue << ", " << secretMessage << ")" << std::endl;
    }
}