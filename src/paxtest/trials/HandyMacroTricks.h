//
// Created by paul on 09.01.19.
//

#ifndef PAXENGINE3_HANDYMACROTRICKS_H
#define PAXENGINE3_HANDYMACROTRICKS_H

// Accept any number of args >= N, but expand to just the Nth one.
// Here, N == 6.
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, N, ...) N

// Define some macros to help us create overrides based on the
// arity of a for-each-style macro.
#define _fe_0(_call, ...)
#define _fe_1(_call, x) _call(x)
#define _fe_2(_call, x, ...) _call(x) _fe_1(_call, __VA_ARGS__)
#define _fe_3(_call, x, ...) _call(x) _fe_2(_call, __VA_ARGS__)
#define _fe_4(_call, x, ...) _call(x) _fe_3(_call, __VA_ARGS__)

#define PAX_CALL_MACRO_X_FOR_EACH(x, ...) \
    _GET_NTH_ARG("ignored", ##__VA_ARGS__, \
_fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(x, ##__VA_ARGS__)


#define GET_1(_1, ...) _1
#define GET_2(_1, _2, ...) __2
#define GET_3(_1, _2, _3, ...) _3

#define _GET_OVERRIDE(_1, _2, _3, NAME, ...) NAME


#define PAX_INTERLEAVE(...) PAX_CALL_MACRO_X_FOR_EACH(_GET_OVERRIDE, __VA_ARGS__)





// Fun with macros
#define PAX_on_odd_1_or_2(op, x, ...) x
#define PAX_on_odd_3_or_4(op, x, y, ...) x op PAX_on_odd_1_or_2(op, __VA_ARGS__)
#define PAX_on_odd_5_or_6(op, x, y, ...) x op PAX_on_odd_3_or_4(op, __VA_ARGS__)

#define PAX_on_even_2_or_3(op, x, y, ...) y
#define PAX_on_even_4_or_5(op, x, y, ...) y op PAX_on_even_2_or_3(op, __VA_ARGS__)
#define PAX_on_even_6_or_7(op, x, y, ...) y op PAX_on_even_4_or_5(op, __VA_ARGS__)

/* Only on GCC
constexpr int odd  = PAX_on_odd_5_or_6(+, 0, 1, 0, 1, 0); // Expected 0
constexpr int even = PAX_on_even_4_or_5(*, 0, 1, 0, 1, 0); // Expected 1

std::cout << "odd  = " << odd << std::endl;
std::cout << "even = " << even << std::endl;
//*/



#endif //PAXENGINE3_HANDYMACROTRICKS_H
