//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxopengl/OpenGLPointCloudSettings.h>
#include <GL/glew.h>

namespace PAX::OpenGL {
    void OpenGLPointCloudSettings::initialize() {
        glEnable(GL_PROGRAM_POINT_SIZE);
    }

    void OpenGLPointCloudSettings::setPointSize(float pointSize) {
        PointCloudSettings::setPointSize(pointSize);
        glPointSize(pointSize);
    }
}