//
// Created by Paul on 30.06.2017.
//

#include <paxutil/macros/MacroIncludes.h>
#include <paxcore/rendering/camera/PerspectiveProjection.h>

namespace PAX {
    PerspectiveProjection::PerspectiveProjection() {
        setFOV(70);
        setNearPlane(0.01f);
        setFarPlane(10000);
    }

    void PerspectiveProjection::calcMatrix() {
        float resX = static_cast<float>(getResolutionWidth());
        float resY = static_cast<float>(getResolutionHeight());
        float near = getNearPlane();
        float far = getFarPlane();

        float aspectRatio = resX / resY;
        float yScale = (1.0f / tan(0.5f * PAX_ToRadians(getFOV()))) * aspectRatio;
        float xScale = yScale / aspectRatio;
        float frustumLength = far - near;

        _matrix = glm::mat4(0);

        _matrix[0][0] = xScale;
        _matrix[1][1] = yScale;
        _matrix[2][2] = -((far + near) / frustumLength);
        _matrix[2][3] = -1;
        _matrix[3][2] = -((2.0f * near * far) / frustumLength);
    }
}