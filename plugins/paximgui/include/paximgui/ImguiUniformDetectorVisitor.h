//
// Created by Paul on 04.09.2022.
//

#ifndef PAXENGINE3_IMGUIUNIFORMDETECTORVISITOR_H
#define PAXENGINE3_IMGUIUNIFORMDETECTORVISITOR_H

#include "ImguiPPParserVisitor.h"
#include "Variable.h"

namespace PAX {
    namespace Imgui {
        class ImguiUniformDetectorVisitor : public Antlr::ImguiPPParserVisitor {
        public:
            Variables variables;

            antlrcpp::Any visitProgram(Antlr::ImguiPPParser::ProgramContext *context) override;
            antlrcpp::Any visitImgui_annotation(Antlr::ImguiPPParser::Imgui_annotationContext *context) override;
            antlrcpp::Any visitImgui_ranged_annotation(Antlr::ImguiPPParser::Imgui_ranged_annotationContext *context) override;
            antlrcpp::Any visitImgui_uniform(Antlr::ImguiPPParser::Imgui_uniformContext *context) override;
        };
    }
}

#endif //PAXENGINE3_IMGUIUNIFORMDETECTORVISITOR_H
