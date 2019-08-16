//
// Created by Paul on 30.06.2017.
//

#include <paxcore/rendering/camera/PerspectiveProjection.h>
#include <paxutil/math/Angles.h>

namespace PAX {
    PerspectiveProjection::PerspectiveProjection() {
        setFOV(70);
        setNearPlane(0.01f);
        setFarPlane(10000);
    }

    void PerspectiveProjection::calcMatrix() {
        Projection::calcMatrix();

        auto resX = static_cast<float>(getResolution().x);
        auto resY = static_cast<float>(getResolution().y);
        float near = getNearPlane();
        float far = getFarPlane();

        float aspectRatio = resX / resY;
        float yScale = static_cast<float>(1.0f / tan(0.5 * Math::toRadians(getFOV()))) * aspectRatio;
        float xScale = yScale / aspectRatio;
        float frustumLength = far - near;

        _matrix[0][0] = xScale;
        _matrix[1][1] = yScale;
        _matrix[2][2] = -((far + near) / frustumLength);
        _matrix[2][3] = -1;
        _matrix[3][2] = -((2.0f * near * far) / frustumLength);
    }

    void PerspectiveProjection::setFOV(float fov) {
        _fov = fov;
        makeDirty();
    }

    float PerspectiveProjection::getFOV() {
        return _fov;
    }

    void PerspectiveProjection::setNearPlane(float nearPlane) {
        _near = nearPlane;
        makeDirty();
    }

    float PerspectiveProjection::getNearPlane() {
        return _near;
    }

    void PerspectiveProjection::setFarPlane(float farPlane) {
        _far = farPlane;
        makeDirty();
    }

    float PerspectiveProjection::getFarPlane() {
        return _far;
    }
}