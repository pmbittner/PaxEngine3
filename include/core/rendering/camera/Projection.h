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
        unsigned int _resWidth, _resHeight;

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

        float getNearPlane();
        void setNearPlane(float nearPlane);

        float getFarPlane();
        void setFarPlane(float farPlane);

        unsigned int getResolutionWidth();
        void setResolutionWidth(unsigned int resolutionWidth);

        unsigned int getResolutionHeight();
        void setResolutionHeight(unsigned int resolutionHeight);
    };
}

#endif //PAXENGINE3_PROJECTION_H
