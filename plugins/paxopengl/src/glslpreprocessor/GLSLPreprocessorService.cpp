//
// Created by Paul Bittner on 04.09.2022.
//

#include "paxopengl/glslpreprocessor/GLSLPreprocessorService.h"

namespace PAX {
    namespace OpenGL {
        GLSLPreprocessorService::~GLSLPreprocessorService() {
            for (GLSLPreprocessor* pp : preprocessors) {
                delete pp;
            }
        }

        void GLSLPreprocessorService::addAndOwnPreprocessor(GLSLPreprocessor * preprocessor) {
            preprocessors.push_back(preprocessor);
        }

        std::string GLSLPreprocessorService::preprocess(const Path & codeFile, const std::string& code) {
            std::string c = code;
            for (GLSLPreprocessor* pp : preprocessors) {
                c = pp->preprocess(codeFile, c);
            }
            return c;
        }
    }
}