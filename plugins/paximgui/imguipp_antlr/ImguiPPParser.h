
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace Antlr {


class  ImguiPPParser : public antlr4::Parser {
public:
  enum {
    WS = 1, SINGLELINE_COMMENT = 2, MULTILINE_COMMENT = 3, LINEBREAK = 4, 
    IMGUI = 5, IMGUI_RANGED = 6, ANYTHING_ELSE = 7, BRACKET_L = 8, BRACKET_R = 9, 
    IDENTIFIER = 10, COMMA = 11, EQUALS = 12, SEMICOLON = 13, UNIFORM_INITIAL_VALUE = 14, 
    UNIFORM_INITIALIZATION_END = 15
  };

  enum {
    RuleProgram = 0, RuleImgui_annotation = 1, RuleImgui_ranged_annotation = 2, 
    RuleImgui_uniform = 3
  };

  explicit ImguiPPParser(antlr4::TokenStream *input);

  ImguiPPParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ImguiPPParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class Imgui_annotationContext;
  class Imgui_ranged_annotationContext;
  class Imgui_uniformContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Imgui_uniformContext *> imgui_uniform();
    Imgui_uniformContext* imgui_uniform(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  Imgui_annotationContext : public antlr4::ParserRuleContext {
  public:
    Imgui_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMGUI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imgui_annotationContext* imgui_annotation();

  class  Imgui_ranged_annotationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *from = nullptr;
    antlr4::Token *to = nullptr;
    Imgui_ranged_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMGUI_RANGED();
    antlr4::tree::TerminalNode *BRACKET_L();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *BRACKET_R();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imgui_ranged_annotationContext* imgui_ranged_annotation();

  class  Imgui_uniformContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *type = nullptr;
    antlr4::Token *name = nullptr;
    antlr4::Token *initialValue = nullptr;
    Imgui_uniformContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    Imgui_annotationContext *imgui_annotation();
    Imgui_ranged_annotationContext *imgui_ranged_annotation();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *UNIFORM_INITIALIZATION_END();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *UNIFORM_INITIAL_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imgui_uniformContext* imgui_uniform();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace Antlr
