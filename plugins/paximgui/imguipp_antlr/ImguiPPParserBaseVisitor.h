
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "ImguiPPParserVisitor.h"


namespace Antlr {

/**
 * This class provides an empty implementation of ImguiPPParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ImguiPPParserBaseVisitor : public ImguiPPParserVisitor {
public:

  virtual std::any visitProgram(ImguiPPParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImgui_annotation(ImguiPPParser::Imgui_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImgui_ranged_annotation(ImguiPPParser::Imgui_ranged_annotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImgui_uniform(ImguiPPParser::Imgui_uniformContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Antlr
