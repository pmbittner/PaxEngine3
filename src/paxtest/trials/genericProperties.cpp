//
// Created by paul on 22.09.18.
//

#include "TestProperties.h"

int main(int argc, char** argv) {
    using namespace PAX;
    {
        ExampleContainer e;

        if (IPropertyFactory<ExampleContainer> *newBla = PropertyFactoryRegister<ExampleContainer>::getFactoryFor(
                "PAX::Bla")) {
            ExampleContentProvider p;
            e.add(newBla->create(p));
        }

        Bla *b = e.get<Bla>();

        if (b) {
            b->bla();
        } else {
            std::cerr << "Could not create PAX::Bla by name" << std::endl;
        }

        std::cout << "Destroying container" << std::endl;
    }

    std::cout << "Done :)" << std::endl;

    return 0;
}