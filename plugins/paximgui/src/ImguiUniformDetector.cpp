//
// Created by Paul on 04.09.2022.
//

#include "paximgui/ImguiUniformDetector.h"
#include "antlr4-runtime.h"
#include "ImguiPPLexer.h"
#include "ImguiPPParser.h"
#include "paximgui/ImguiUniformDetectorVisitor.h"
#include "paxutil/io/PrettyPrint.h"

namespace PAX {
    namespace Imgui {
        ImguiUniformDetector::ImguiUniformDetector() = default;

        ImguiUniformDetector::~ImguiUniformDetector() = default;

        std::string ImguiUniformDetector::preprocess(const PAX::Path &codeFile, const std::string &code) {
            currentCode = &code;

            antlr4::ANTLRInputStream input(code);
            Antlr::ImguiPPLexer lexer(&input);
            antlr4::CommonTokenStream tokens(&lexer);
            Antlr::ImguiPPParser parser(&tokens);
            parser.addErrorListener(this);

            ImguiUniformDetectorVisitor visitor;
            visitor.visitProgram(parser.program());
            OnUniformsDetected(visitor.variables);

            currentCode = nullptr;

            return code;
        }

        void ImguiUniformDetector::syntaxError(
                antlr4::Recognizer *recognizer,
                antlr4::Token *offendingSymbol,
                size_t line,
                size_t charPositionInLine,
                const std::string &msg,
                std::exception_ptr e) {
            std::stringstream output;
            output << "Parsing Error at line " << line << " at character " << charPositionInLine << ": " << msg << std::endl;
            if (currentCode) {
                output << "Full Shader Code:\n------------------\n";
                Util::printWithLineNumbersTo(output, *currentCode);
                output << "==================";
            }
            PAX_LOG(Log::Level::Error, output.str());
        }
    }
}