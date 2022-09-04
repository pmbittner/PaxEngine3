
// Generated from ImguiPPLexer.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"


namespace Antlr {


class  ImguiPPLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, SINGLELINE_COMMENT = 2, MULTILINE_COMMENT = 3, LINEBREAK = 4, 
    IMGUI = 5, IMGUI_RANGED = 6, ANYTHING_ELSE = 7, BRACKET_L = 8, BRACKET_R = 9, 
    IDENTIFIER = 10, COMMA = 11, EQUALS = 12, SEMICOLON = 13, UNIFORM_INITIAL_VALUE = 14, 
    UNIFORM_INITIALIZATION_END = 15
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
