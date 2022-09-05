
// Generated from ImguiPPLexer.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace Antlr {


class  ImguiPPLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, SINGLELINE_COMMENT = 2, MULTILINE_COMMENT = 3, MACRO_LINE = 4, 
    LINEBREAK = 5, IMGUI = 6, IMGUI_RANGED = 7, ANYTHING_ELSE = 8, WS2 = 9, 
    BRACKET_L = 10, BRACKET_R = 11, IDENTIFIER = 12, COMMA = 13, EQUALS = 14, 
    SEMICOLON = 15, UNIFORM_INITIAL_VALUE = 16, UNIFORM_INITIALIZATION_END = 17
  };

  enum {
    IMGUI_ANNOTATION_MODE = 1, UNIFORM_INITIALIZATION = 2
  };

  explicit ImguiPPLexer(antlr4::CharStream *input);

  ~ImguiPPLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace Antlr
