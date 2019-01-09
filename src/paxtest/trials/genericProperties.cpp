//
// Created by paul on 22.09.18.
//

#include "TestProperties.h"

int main(int argc, char** argv) {
    using namespace PAX;

    ExampleContainer e;

    PropertyContainerPrefab<ExampleContainer> p({
        "PAX::Bla"
    });
    p.createProperties(e);

    Bla* b = e.get<Bla>();

    if (b) {
        b->bla();
    } else {
        std::cerr << "Could not create PAX::Bla by name" << std::endl;
    }

    return 0;
}