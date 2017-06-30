//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_PROJECTION_H
#define PAXENGINE3_PROJECTION_H

#include <glm/glm.hpp>

namespace PAX {
    class Projection {
    private:
        bool _dirty = true;
        float _fov, _near, _far;

    protected:
        glm::mat4 _matrix;
        virtual void calcMatrix() = 0;

    public:
        const glm::mat4& toMatrix();

        /**
         * @param fov field of view in degrees
         */
        void setFOV(float fov);

        /**
         * @return field of view in degrees
         */
        float getFOV();

        void setNearPlane(float nearPlane);
        float getNearPlane();

        float getFarPlane();
        void setFarPlane(float farPlane);
    };
}

#endif //PAXENGINE3_PROJECTION_H
