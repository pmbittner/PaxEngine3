//
// Created by Paul Bittner on 04.09.2022.
//

#include "paxopengl/glslpreprocessor/GLSLIncludeDirectives.h"
#include "paxopengl/resource/OpenGLShader.h"

#include "polypropylene/stdutils/CollectionUtils.h"

namespace PAX {
    namespace OpenGL {
        static std::string eatPrefix(const std::string & str, const std::string & prefix) {
            std::string remains = str.substr(prefix.length());
            String::ltrim(remains);
            return remains;
        }

        std::string GLSLIncludeDirectives::resolveIncludes(
                const PAX::Path &codeFile,
                const std::string &code,
                const std::vector<Path> &alreadyIncludedFiles) {
            static constexpr const char LINEBREAK = '\n';
            std::string output;
            std::stringstream codeAsStream(code);
            std::string line;
            int lineno = -1;

            while (std::getline(codeAsStream, line, LINEBREAK)) {
                ++lineno;

                if (String::startsWith(line, "#")) {
                    std::string macro = eatPrefix(line, "#");

                    if (String::startsWith(macro, "include")) {
                        macro = eatPrefix(macro, "include");

                        Path includeFile = codeFile.getDirectory() + macro;
                        includeFile.simplify();

                        if (Util::vectorContains(alreadyIncludedFiles, includeFile)) {
                            PAX_THROW_RUNTIME_ERROR(
                                    "Cyclic include: file " << includeFile << " included at line " << lineno << " in "
                                                            << codeFile << " was already included!");
                        }

                        // Only remember the inclusion of the file for the inclusion of it, to detect cyclic includes.
                        // We forget about this include afterwards to not fail on duplicate includes, which would prevent
                        // modularity and hiding.
                        std::vector<Path> nowIncludedFiles = alreadyIncludedFiles;
                        nowIncludedFiles.push_back(includeFile);
                        std::string includeContent = OpenGLShader::LoadCodeFromFile(includeFile);
                        output += resolveIncludes(includeFile, includeContent, nowIncludedFiles);
                        continue;
                    }
                }

                output += line + LINEBREAK;
            }

            return output;
        }

        std::string GLSLIncludeDirectives::preprocess(const Path & codeFile, const std::string &code) {
            return resolveIncludes(codeFile, code, {});
        }
    }
}