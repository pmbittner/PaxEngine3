//
// Created by Paul Bittner on 04.09.2022.
//

#ifndef PAXENGINE3_GLSLPREPROCESSORSERVICE_H
#define PAXENGINE3_GLSLPREPROCESSORSERVICE_H

#include "GLSLPreprocessor.h"

#include <vector>

namespace PAX {
    namespace OpenGL {
        class GLSLPreprocessorService {
            std::vector<GLSLPreprocessor*> preprocessors;

        public:
            ~GLSLPreprocessorService();

            /**
             * Adds the given preprocessor to this service.
             * Takes ownership and assumes the given preprocessor to be allocated on the heap via "new".
             * @param preprocessor
             */
            void addAndOwnPreprocessor(GLSLPreprocessor * preprocessor);

            std::string preprocess(const Path & codeFile, const std::string& code);
        };
    }
}

#endif //PAXENGINE3_GLSLPREPROCESSORSERVICE_H
