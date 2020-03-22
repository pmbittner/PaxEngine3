//
// Created by Paul Bittner on 21.03.2020.
//

#include <paxopengl/OpenGLPointCloudSettings.h>
#include <GL/glew.h>

namespace PAX::OpenGL {
    void OpenGLPointCloudSettings::initialize() {
        //glEnable( GL_POINT_SMOOTH );
        //glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        //glEnable(GL_POINT_SPRITE);
    }

    void OpenGLPointCloudSettings::setPointSize(float pointSize) {
        PointCloudSettings::setPointSize(pointSize);
        glPointSize(pointSize);
    }

    void OpenGLPointCloudSettings::init(PAX::Shader *shader) {
        shader->bind();
        glEnable(GL_PROGRAM_POINT_SIZE);
        shader->unbind();
    }
}