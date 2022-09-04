
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "ImguiPPParser.h"


namespace Antlr {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by ImguiPPParser.
 */
class  ImguiPPParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ImguiPPParser.
   */
    virtual std::any visitProgram(ImguiPPParser::ProgramContext *context) = 0;

    virtual std::any visitImgui_annotation(ImguiPPParser::Imgui_annotationContext *context) = 0;

    virtual std::any visitImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext *context) = 0;

    virtual std::any visitImgui_uniform(ImguiPPParser::Imgui_uniformContext *context) = 0;


};

}  // namespace Antlr
