//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_PERSPECTIVEPROJECTION_H
#define PAXENGINE3_PERSPECTIVEPROJECTION_H

#include "Projection.h"

namespace PAX {
    class PerspectiveProjection : public Projection {
    public:
        PerspectiveProjection();
        virtual void calcMatrix() override;
    };
}

#endif //PAXENGINE3_PERSPECTIVEPROJECTION_H
