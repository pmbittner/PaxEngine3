//
// Created by paul on 22.09.18.
//

#include "TestProperties.h"

int main(int argc, char** argv) {
    using namespace PAX;

    ExampleContainer e;

    if (IPropertyFactory<ExampleContainer> * newBla = PropertyFactoryRegister<ExampleContainer>::getFactoryFor("PAX::Bla")) {
        ContentProvider p;
        e.add(newBla->create(p));
    }

    Bla* b = e.get<Bla>();

    if (b) {
        b->bla();
    } else {
        std::cerr << "Could not create PAX::Bla by name" << std::endl;
    }

    /*/{
        Bla * b0 = Bla::create();
        Bla * b1 = Bla::create(42);
        Bla * b2 = Bla::create(24, "moin");

        b0->bla();
        b1->bla();
        b2->bla();
    }//*/

    return 0;
}