//
// Created by Paul on 04.09.2022.
//

#include "paximgui/ImguiUniformDetector.h"
#include "antlr4-runtime.h"
#include "ImguiPPLexer.h"
#include "ImguiPPParser.h"
#include "paximgui/ImguiUniformDetectorVisitor.h"

namespace PAX {
    namespace Imgui {
        ImguiUniformDetector::~ImguiUniformDetector() = default;

        std::string ImguiUniformDetector::preprocess(const PAX::Path &codeFile, const std::string &code) {
            antlr4::ANTLRInputStream input(code);
            Antlr::ImguiPPLexer lexer(&input);
            antlr4::CommonTokenStream tokens(&lexer);
            Antlr::ImguiPPParser parser(&tokens);

            ImguiUniformDetectorVisitor visitor;
            visitor.visitProgram(parser.program());
            OnUniformsDetected(visitor.variables);

            return code;
        }
    }
}