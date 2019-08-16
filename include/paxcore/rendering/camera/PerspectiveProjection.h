//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_PERSPECTIVEPROJECTION_H
#define PAXENGINE3_PERSPECTIVEPROJECTION_H

#include "Projection.h"

namespace PAX {
    class PerspectiveProjection : public Projection {
        float _fov = 90, _near = 0.1f, _far = 1000;
        
    public:
        PerspectiveProjection();
        virtual void calcMatrix() override;

        /**
         * @param fov field of view in degrees
         */
        void setFOV(float fov);

        /**
         * @return field of view in degrees
         */
        float getFOV();

        float getNearPlane();
        void setNearPlane(float nearPlane);

        float getFarPlane();
        void setFarPlane(float farPlane);
    };
}

#endif //PAXENGINE3_PERSPECTIVEPROJECTION_H
