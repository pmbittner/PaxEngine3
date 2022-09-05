//
// Created by Paul on 04.09.2022.
//

#ifndef PAXENGINE3_IMGUIUNIFORMDETECTOR_H
#define PAXENGINE3_IMGUIUNIFORMDETECTOR_H

#include "paxopengl/glslpreprocessor/GLSLPreprocessor.h"
#include "polypropylene/event/EventHandler.h"

#include "Variable.h"
#include "BaseErrorListener.h"

namespace PAX {
    namespace Imgui {
        class ImguiUniformDetector : public OpenGL::GLSLPreprocessor, public antlr4::BaseErrorListener {
            const std::string * currentCode = nullptr;

        public:
            EventHandler<Variables&> OnUniformsDetected;

            ImguiUniformDetector();
            ~ImguiUniformDetector() override;
            std::string preprocess(const Path & codeFile, const std::string& code) override;

            void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol,
                             size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;
        };
    }
}

#endif //PAXENGINE3_IMGUIUNIFORMDETECTOR_H
