//
// Created by Paul on 09.07.2017.
//

#ifndef PAXENGINE3_FULLPIXELSCREENPROJECTION_H
#define PAXENGINE3_FULLPIXELSCREENPROJECTION_H

#include "PixelScreenProjection.h"

namespace PAX {
    class FullPixelScreenProjection : public PixelScreenProjection {
        int _coordWidth, _coordHeight;

    public:
        FullPixelScreenProjection(int coordinateSystemWidth = 800, int coordinateSystemHeight = 600);
        virtual void calcMatrix() override;

        void setCoordinateSystemWidth(int width);
        int getCoordinateSystemWidth();

        void setCoordinateSystemHeight(int width);
        int getCoordinateSystemHeight();
    };
}

#endif //PAXENGINE3_FULLPIXELSCREENPROJECTION_H
