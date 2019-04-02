//
// Created by Bittner on 02/04/2019.
//

#ifndef PAXENGINE3_OPENGLERROR_H
#define PAXENGINE3_OPENGLERROR_H

#include <string>
#include <GL/glew.h>
#include <iostream>

#include <paxutil/macros/BuildType.h>

namespace PAX {
    namespace OpenGL {

#define PAX_CRASH_ON_GLERROR

        // Automatic version
        void GLAPIENTRY
        GLErrorCallback( GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar* message,
                         const void* userParam);

        // Manual version
        bool getGLError(const std::string & location);

#if defined(PAX_BUILD_TYPE_DEBUG)
    #define PAX_GLERROR(str_location) getGLError(str_location)
#elif defined(PAX_BUILD_TYPE_RELEASE)
    #define PAX_GLERROR(str_location) false
#endif
    }
}

#endif //PAXENGINE3_OPENGLERROR_H
