//
// Created by Paul on 07.01.2018.
//

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "paxopengl/utility/Error.h"

namespace PAX {
    namespace OpenGL {
        bool catchError(std::string msg, bool failOnError)
        {
            // check OpenGL error
            GLenum err;
            bool err_occured = false;
            while ((err = glGetError()) != GL_NO_ERROR) {
                err_occured = true;
                if (msg == "") {
                    std::cerr << "OpenGL error : " << err << std::endl;
                }
                else {
                    std::cerr << "OpenGL error ( " << msg << " ) : " << err << "  " << gluErrorString(err)<<  std::endl;
                }
            }
            if (failOnError && err_occured) {
                throw std::runtime_error("Unclean OpenGL State");
            }

            return err_occured;
        }
    }
}