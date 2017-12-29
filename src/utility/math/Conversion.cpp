//
// Created by Paul on 29.12.2017.
//

#include <utility/math/Conversion.h>
#include <assert.h>

int PAX::Util::Conversion::coordinatesToIndex(int w, int x, int y) {
    assert(x < w);
    return (w*y)+x;
}