//
// Created by Paul Bittner on 04.09.2022.
//

#ifndef PAXENGINE3_GLSLPREPROCESSOR_H
#define PAXENGINE3_GLSLPREPROCESSOR_H

#include <string>
#include "polypropylene/io/Path.h"

namespace PAX {
    namespace OpenGL {
        class GLSLPreprocessor {
        public:
            virtual ~GLSLPreprocessor() = 0 {};
            virtual std::string preprocess(const Path & codeFile, const std::string& code) = 0;
        };
    }
}

#endif //PAXENGINE3_GLSLPREPROCESSOR_H
