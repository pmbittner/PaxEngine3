//
// Created by paul on 22.09.18.
//

#include "TestProperties.h"

// Fun with macros
#define PAX_on_odd_1_or_2(op, x, ...) x
#define PAX_on_odd_3_or_4(op, x, y, ...) x op PAX_on_odd_1_or_2(op, __VA_ARGS__)
#define PAX_on_odd_5_or_6(op, x, y, ...) x op PAX_on_odd_3_or_4(op, __VA_ARGS__)

#define PAX_on_even_2_or_3(op, x, y, ...) y
#define PAX_on_even_4_or_5(op, x, y, ...) y op PAX_on_even_2_or_3(op, __VA_ARGS__)
#define PAX_on_even_6_or_7(op, x, y, ...) y op PAX_on_even_4_or_5(op, __VA_ARGS__)

#define PAX_ON_ODD_INDEXES(op, ...) PAX_on_odd_5(op, __VA_ARGS__)

int main(int argc, char** argv) {
    using namespace PAX;

    ExampleContainer e;

    {
        using Factory = PropertyFactory<ExampleContainer>;
        const Factory::Constructor & newBla = Factory::getFactoryFor("PAX::Bla");

        if (newBla.isValid()) {
            ContentProvider p;
            e.add(newBla(p));
        }
    }

    Bla* b = e.get<Bla>();

    if (b) {
        b->bla();
    } else {
        std::cerr << "Could not create PAX::Bla by name" << std::endl;
    }

    constexpr int odd  = PAX_on_odd_5_or_6(+, 0, 1, 0, 1, 0); // Expected 0
    constexpr int even = PAX_on_even_4_or_5(*, 0, 1, 0, 1, 0); // Expected 1

    std::cout << "odd  = " << odd << std::endl;
    std::cout << "even = " << even << std::endl;

    return 0;
}