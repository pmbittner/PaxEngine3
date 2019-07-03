//
// Created by Paul on 30.06.2017.
//

#include <paxutil/macros/MacroIncludes.h>
#include <paxcore/rendering/camera/PixelScreenProjection.h>

namespace PAX {
    PixelScreenProjection::PixelScreenProjection() {
        setNearPlane(0.01f);
        setFarPlane(10000);
    }

    void PixelScreenProjection::calcMatrix() {
        float resX = static_cast<float>(getResolution().x);
        float resY = static_cast<float>(getResolution().y);
        float near = getNearPlane();
        float far = getFarPlane();
        float invFrustumLength = 1.0f / (far - near);

        _matrix = glm::mat4(0);

        _matrix[0][0] = 2.0f / resX;
        _matrix[1][1] = 2.0f / resY;
        _matrix[2][2] = -2.0f * invFrustumLength;
        _matrix[3][2] = -((far + near) * invFrustumLength);
        _matrix[3][3] = 1.0f;
    }
}