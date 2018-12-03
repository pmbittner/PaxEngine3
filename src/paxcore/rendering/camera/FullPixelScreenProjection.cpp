//
// Created by Paul on 09.07.2017.
//
#include <iostream>
#include <paxcore/rendering/camera/FullPixelScreenProjection.h>

namespace PAX {
    FullPixelScreenProjection::FullPixelScreenProjection(int coordinateSystemWidth, int coordinateSystemHeight) : PixelScreenProjection() {
        _coordWidth = coordinateSystemWidth;
        _coordHeight = coordinateSystemHeight;
    }

    void FullPixelScreenProjection::calcMatrix() {
        PixelScreenProjection::calcMatrix();

        float widthScale = getResolution().x / static_cast<float>(_coordWidth);
        float heightScale = getResolution().y / static_cast<float>(_coordHeight);

        for (int col = 0; col < 4; ++col) {
            _matrix[col][0] *= widthScale;
            _matrix[col][1] *= heightScale;
        }
    }
}