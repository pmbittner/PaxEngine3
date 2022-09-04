//
// Created by Paul Bittner on 04.09.2022.
//

#ifndef PAXENGINE3_GLSLINCLUDEDIRECTIVES_H
#define PAXENGINE3_GLSLINCLUDEDIRECTIVES_H

#include "GLSLPreprocessor.h"

namespace PAX {
    namespace OpenGL {
        /**
         * Adds the ability for "#include" directives to GLSL.
         * Syntax: "#include <file>", where file is a path to another
         *         file to include, without quotes. Example:
         *         #include lib/math.glsl
         */
        class GLSLIncludeDirectives : public GLSLPreprocessor {
            std::string resolveIncludes(const Path & codeFile, const std::string& code, const std::vector<Path> & alreadyIncludedFiles);

        public:
            ~GLSLIncludeDirectives() override = default;
            std::string preprocess(const Path & codeFile, const std::string& code) override;
        };
    }
}

#endif //PAXENGINE3_GLSLINCLUDEDIRECTIVES_H
