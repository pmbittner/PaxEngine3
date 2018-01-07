//
// Created by Paul on 07.01.2018.
//

#include <GL/glew.h>
#include <opengl/utility/Error.h>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

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