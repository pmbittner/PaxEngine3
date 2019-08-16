//
// Created by Paul on 30.06.2017.
//

#include <paxcore/rendering/camera/PixelScreenProjection.h>

namespace PAX {
    void PixelScreenProjection::calcMatrix() {
        Projection::calcMatrix();

        _matrix[0][0] = 2.0f / getResolution().x;
        _matrix[1][1] = 2.0f / getResolution().y;

        // This is the inverse frustum length.
        // In our case it should actually be zero so that all elements get projected to z = 0.
        // But then, the matrix would not be invertible.
        // Hence, we use this really small value denoting,
        // that we have a very large potential frustum, i.e., a very large range for z.
        _matrix[2][2] = 0.0000000001f;
    }
}