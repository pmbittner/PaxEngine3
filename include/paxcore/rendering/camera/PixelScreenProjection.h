//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_ORTHOGRAPHICPROJECTION_H
#define PAXENGINE3_ORTHOGRAPHICPROJECTION_H

#include "Projection.h"

namespace PAX {
    class PixelScreenProjection : public Projection {
    public:
        PixelScreenProjection();
        virtual void calcMatrix() override;
    };
}

#endif //PAXENGINE3_ORTHOGRAPHICPROJECTION_H
