
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "ImguiPPParser.h"


namespace Antlr {

/**
 * This interface defines an abstract listener for a parse tree produced by ImguiPPParser.
 */
class  ImguiPPParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(ImguiPPParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(ImguiPPParser::ProgramContext *ctx) = 0;

  virtual void enterImgui_annotation(ImguiPPParser::Imgui_annotationContext *ctx) = 0;
  virtual void exitImgui_annotation(ImguiPPParser::Imgui_annotationContext *ctx) = 0;

  virtual void enterImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext *ctx) = 0;
  virtual void exitImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext *ctx) = 0;

  virtual void enterImgui_uniform(ImguiPPParser::Imgui_uniformContext *ctx) = 0;
  virtual void exitImgui_uniform(ImguiPPParser::Imgui_uniformContext *ctx) = 0;


};

}  // namespace Antlr
