//
// Created by Paul on 07.01.2018.
//

#ifndef PAXENGINE3_ERROR_H
#define PAXENGINE3_ERROR_H

#include <string>

namespace PAX {
    namespace OpenGL {
        bool catchError(std::string msg = "", bool failOnError = false);
    }
}

#endif //PAXENGINE3_ERROR_H
