
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "ImguiPPParserListener.h"


namespace Antlr {

/**
 * This class provides an empty implementation of ImguiPPParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ImguiPPParserBaseListener : public ImguiPPParserListener {
public:

  virtual void enterProgram(ImguiPPParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(ImguiPPParser::ProgramContext * /*ctx*/) override { }

  virtual void enterImgui_annotation(ImguiPPParser::Imgui_annotationContext * /*ctx*/) override { }
  virtual void exitImgui_annotation(ImguiPPParser::Imgui_annotationContext * /*ctx*/) override { }

  virtual void enterImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext * /*ctx*/) override { }
  virtual void exitImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext * /*ctx*/) override { }

  virtual void enterImgui_uniform(ImguiPPParser::Imgui_uniformContext * /*ctx*/) override { }
  virtual void exitImgui_uniform(ImguiPPParser::Imgui_uniformContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace Antlr
