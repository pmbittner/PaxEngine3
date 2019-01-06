//
// Created by paul on 06.01.19.
//

#include "TestProperties.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Bla)

    Bla::Bla() {
        secretMessage = "Morgenroete";
    }

    void Bla::bla() {
        std::cout << "[PAX::Example::bla] " << secretMessage << std::endl;
    }
}