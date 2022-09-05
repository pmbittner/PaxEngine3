
// Generated from ImguiPPParser.g4 by ANTLR 4.10.1


#include "ImguiPPParserListener.h"
#include "ImguiPPParserVisitor.h"

#include "ImguiPPParser.h"


using namespace antlrcpp;
using namespace Antlr;

using namespace antlr4;

namespace {

struct ImguiPPParserStaticData final {
  ImguiPPParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ImguiPPParserStaticData(const ImguiPPParserStaticData&) = delete;
  ImguiPPParserStaticData(ImguiPPParserStaticData&&) = delete;
  ImguiPPParserStaticData& operator=(const ImguiPPParserStaticData&) = delete;
  ImguiPPParserStaticData& operator=(ImguiPPParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag imguippparserParserOnceFlag;
ImguiPPParserStaticData *imguippparserParserStaticData = nullptr;

void imguippparserParserInitialize() {
  assert(imguippparserParserStaticData == nullptr);
  auto staticData = std::make_unique<ImguiPPParserStaticData>(
    std::vector<std::string>{
      "program", "imgui_annotation", "imgui_ranged_annotation", "imgui_uniform"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "'IMGUI_RANGED'", "", "", "'('", "')'", 
      "", "','", "'='"
    },
    std::vector<std::string>{
      "", "WS", "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "MACRO_LINE", 
      "LINEBREAK", "IMGUI", "IMGUI_RANGED", "ANYTHING_ELSE", "WS2", "BRACKET_L", 
      "BRACKET_R", "IDENTIFIER", "COMMA", "EQUALS", "SEMICOLON", "UNIFORM_INITIAL_VALUE", 
      "UNIFORM_INITIALIZATION_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,17,38,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,5,0,10,8,0,10,0,12,0,13,
  	9,0,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,3,3,28,8,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,3,3,36,8,3,1,3,0,0,4,0,2,4,6,0,0,36,0,11,1,0,0,
  	0,2,16,1,0,0,0,4,18,1,0,0,0,6,27,1,0,0,0,8,10,3,6,3,0,9,8,1,0,0,0,10,
  	13,1,0,0,0,11,9,1,0,0,0,11,12,1,0,0,0,12,14,1,0,0,0,13,11,1,0,0,0,14,
  	15,5,0,0,1,15,1,1,0,0,0,16,17,5,6,0,0,17,3,1,0,0,0,18,19,5,7,0,0,19,20,
  	5,10,0,0,20,21,5,12,0,0,21,22,5,13,0,0,22,23,5,12,0,0,23,24,5,11,0,0,
  	24,5,1,0,0,0,25,28,3,2,1,0,26,28,3,4,2,0,27,25,1,0,0,0,27,26,1,0,0,0,
  	28,29,1,0,0,0,29,30,5,12,0,0,30,35,5,12,0,0,31,32,5,14,0,0,32,33,5,16,
  	0,0,33,36,5,17,0,0,34,36,5,15,0,0,35,31,1,0,0,0,35,34,1,0,0,0,36,7,1,
  	0,0,0,3,11,27,35
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  imguippparserParserStaticData = staticData.release();
}

}

ImguiPPParser::ImguiPPParser(TokenStream *input) : ImguiPPParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ImguiPPParser::ImguiPPParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ImguiPPParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *imguippparserParserStaticData->atn, imguippparserParserStaticData->decisionToDFA, imguippparserParserStaticData->sharedContextCache, options);
}

ImguiPPParser::~ImguiPPParser() {
  delete _interpreter;
}

const atn::ATN& ImguiPPParser::getATN() const {
  return *imguippparserParserStaticData->atn;
}

std::string ImguiPPParser::getGrammarFileName() const {
  return "ImguiPPParser.g4";
}

const std::vector<std::string>& ImguiPPParser::getRuleNames() const {
  return imguippparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& ImguiPPParser::getVocabulary() const {
  return imguippparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ImguiPPParser::getSerializedATN() const {
  return imguippparserParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

ImguiPPParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ImguiPPParser::ProgramContext::EOF() {
  return getToken(ImguiPPParser::EOF, 0);
}

std::vector<ImguiPPParser::Imgui_uniformContext *> ImguiPPParser::ProgramContext::imgui_uniform() {
  return getRuleContexts<ImguiPPParser::Imgui_uniformContext>();
}

ImguiPPParser::Imgui_uniformContext* ImguiPPParser::ProgramContext::imgui_uniform(size_t i) {
  return getRuleContext<ImguiPPParser::Imgui_uniformContext>(i);
}


size_t ImguiPPParser::ProgramContext::getRuleIndex() const {
  return ImguiPPParser::RuleProgram;
}

void ImguiPPParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void ImguiPPParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any ImguiPPParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ImguiPPParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

ImguiPPParser::ProgramContext* ImguiPPParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, ImguiPPParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(11);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ImguiPPParser::IMGUI

    || _la == ImguiPPParser::IMGUI_RANGED) {
      setState(8);
      imgui_uniform();
      setState(13);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(14);
    match(ImguiPPParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imgui_annotationContext ------------------------------------------------------------------

ImguiPPParser::Imgui_annotationContext::Imgui_annotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ImguiPPParser::Imgui_annotationContext::IMGUI() {
  return getToken(ImguiPPParser::IMGUI, 0);
}


size_t ImguiPPParser::Imgui_annotationContext::getRuleIndex() const {
  return ImguiPPParser::RuleImgui_annotation;
}

void ImguiPPParser::Imgui_annotationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImgui_annotation(this);
}

void ImguiPPParser::Imgui_annotationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImgui_annotation(this);
}


std::any ImguiPPParser::Imgui_annotationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ImguiPPParserVisitor*>(visitor))
    return parserVisitor->visitImgui_annotation(this);
  else
    return visitor->visitChildren(this);
}

ImguiPPParser::Imgui_annotationContext* ImguiPPParser::imgui_annotation() {
  Imgui_annotationContext *_localctx = _tracker.createInstance<Imgui_annotationContext>(_ctx, getState());
  enterRule(_localctx, 2, ImguiPPParser::RuleImgui_annotation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
    match(ImguiPPParser::IMGUI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imgui_ranged_annotationContext ------------------------------------------------------------------

ImguiPPParser::Imgui_ranged_annotationContext::Imgui_ranged_annotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ImguiPPParser::Imgui_ranged_annotationContext::IMGUI_RANGED() {
  return getToken(ImguiPPParser::IMGUI_RANGED, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_ranged_annotationContext::BRACKET_L() {
  return getToken(ImguiPPParser::BRACKET_L, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_ranged_annotationContext::COMMA() {
  return getToken(ImguiPPParser::COMMA, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_ranged_annotationContext::BRACKET_R() {
  return getToken(ImguiPPParser::BRACKET_R, 0);
}

std::vector<tree::TerminalNode *> ImguiPPParser::Imgui_ranged_annotationContext::IDENTIFIER() {
  return getTokens(ImguiPPParser::IDENTIFIER);
}

tree::TerminalNode* ImguiPPParser::Imgui_ranged_annotationContext::IDENTIFIER(size_t i) {
  return getToken(ImguiPPParser::IDENTIFIER, i);
}


size_t ImguiPPParser::Imgui_ranged_annotationContext::getRuleIndex() const {
  return ImguiPPParser::RuleImgui_ranged_annotation;
}

void ImguiPPParser::Imgui_ranged_annotationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImgui_ranged_annotation(this);
}

void ImguiPPParser::Imgui_ranged_annotationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImgui_ranged_annotation(this);
}


std::any ImguiPPParser::Imgui_ranged_annotationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ImguiPPParserVisitor*>(visitor))
    return parserVisitor->visitImgui_ranged_annotation(this);
  else
    return visitor->visitChildren(this);
}

ImguiPPParser::Imgui_ranged_annotationContext* ImguiPPParser::imgui_ranged_annotation() {
  Imgui_ranged_annotationContext *_localctx = _tracker.createInstance<Imgui_ranged_annotationContext>(_ctx, getState());
  enterRule(_localctx, 4, ImguiPPParser::RuleImgui_ranged_annotation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(ImguiPPParser::IMGUI_RANGED);
    setState(19);
    match(ImguiPPParser::BRACKET_L);
    setState(20);
    antlrcpp::downCast<Imgui_ranged_annotationContext *>(_localctx)->from = match(ImguiPPParser::IDENTIFIER);
    setState(21);
    match(ImguiPPParser::COMMA);
    setState(22);
    antlrcpp::downCast<Imgui_ranged_annotationContext *>(_localctx)->to = match(ImguiPPParser::IDENTIFIER);
    setState(23);
    match(ImguiPPParser::BRACKET_R);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imgui_uniformContext ------------------------------------------------------------------

ImguiPPParser::Imgui_uniformContext::Imgui_uniformContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ImguiPPParser::Imgui_uniformContext::IDENTIFIER() {
  return getTokens(ImguiPPParser::IDENTIFIER);
}

tree::TerminalNode* ImguiPPParser::Imgui_uniformContext::IDENTIFIER(size_t i) {
  return getToken(ImguiPPParser::IDENTIFIER, i);
}

ImguiPPParser::Imgui_annotationContext* ImguiPPParser::Imgui_uniformContext::imgui_annotation() {
  return getRuleContext<ImguiPPParser::Imgui_annotationContext>(0);
}

ImguiPPParser::Imgui_ranged_annotationContext* ImguiPPParser::Imgui_uniformContext::imgui_ranged_annotation() {
  return getRuleContext<ImguiPPParser::Imgui_ranged_annotationContext>(0);
}

tree::TerminalNode* ImguiPPParser::Imgui_uniformContext::EQUALS() {
  return getToken(ImguiPPParser::EQUALS, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_uniformContext::UNIFORM_INITIALIZATION_END() {
  return getToken(ImguiPPParser::UNIFORM_INITIALIZATION_END, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_uniformContext::SEMICOLON() {
  return getToken(ImguiPPParser::SEMICOLON, 0);
}

tree::TerminalNode* ImguiPPParser::Imgui_uniformContext::UNIFORM_INITIAL_VALUE() {
  return getToken(ImguiPPParser::UNIFORM_INITIAL_VALUE, 0);
}


size_t ImguiPPParser::Imgui_uniformContext::getRuleIndex() const {
  return ImguiPPParser::RuleImgui_uniform;
}

void ImguiPPParser::Imgui_uniformContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImgui_uniform(this);
}

void ImguiPPParser::Imgui_uniformContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ImguiPPParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImgui_uniform(this);
}


std::any ImguiPPParser::Imgui_uniformContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ImguiPPParserVisitor*>(visitor))
    return parserVisitor->visitImgui_uniform(this);
  else
    return visitor->visitChildren(this);
}

ImguiPPParser::Imgui_uniformContext* ImguiPPParser::imgui_uniform() {
  Imgui_uniformContext *_localctx = _tracker.createInstance<Imgui_uniformContext>(_ctx, getState());
  enterRule(_localctx, 6, ImguiPPParser::RuleImgui_uniform);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ImguiPPParser::IMGUI: {
        setState(25);
        imgui_annotation();
        break;
      }

      case ImguiPPParser::IMGUI_RANGED: {
        setState(26);
        imgui_ranged_annotation();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(29);
    antlrcpp::downCast<Imgui_uniformContext *>(_localctx)->type = match(ImguiPPParser::IDENTIFIER);
    setState(30);
    antlrcpp::downCast<Imgui_uniformContext *>(_localctx)->name = match(ImguiPPParser::IDENTIFIER);
    setState(35);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ImguiPPParser::EQUALS: {
        setState(31);
        match(ImguiPPParser::EQUALS);
        setState(32);
        antlrcpp::downCast<Imgui_uniformContext *>(_localctx)->initialValue = match(ImguiPPParser::UNIFORM_INITIAL_VALUE);
        setState(33);
        match(ImguiPPParser::UNIFORM_INITIALIZATION_END);
        break;
      }

      case ImguiPPParser::SEMICOLON: {
        setState(34);
        match(ImguiPPParser::SEMICOLON);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ImguiPPParser::initialize() {
  std::call_once(imguippparserParserOnceFlag, imguippparserParserInitialize);
}
