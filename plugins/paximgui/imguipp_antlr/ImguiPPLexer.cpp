
// Generated from ImguiPPLexer.g4 by ANTLR 4.10.1


#include "ImguiPPLexer.h"


using namespace antlr4;

using namespace Antlr;


using namespace antlr4;

namespace {

struct ImguiPPLexerStaticData final {
  ImguiPPLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ImguiPPLexerStaticData(const ImguiPPLexerStaticData&) = delete;
  ImguiPPLexerStaticData(ImguiPPLexerStaticData&&) = delete;
  ImguiPPLexerStaticData& operator=(const ImguiPPLexerStaticData&) = delete;
  ImguiPPLexerStaticData& operator=(ImguiPPLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag imguipplexerLexerOnceFlag;
ImguiPPLexerStaticData *imguipplexerLexerStaticData = nullptr;

void imguipplexerLexerInitialize() {
  assert(imguipplexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<ImguiPPLexerStaticData>(
    std::vector<std::string>{
      "WS", "SINGLELINE_COMMENT", "MULTILINE_COMMENT", "MACRO_LINE", "LINEBREAK", 
      "IMGUI", "IMGUI_RANGED", "ANYTHING_ELSE", "WS2", "BRACKET_L", "BRACKET_R", 
      "IDENTIFIER", "COMMA", "EQUALS", "SEMICOLON", "UNIFORM_INITIAL_VALUE", 
      "UNIFORM_INITIALIZATION_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "IMGUI_ANNOTATION_MODE", "UNIFORM_INITIALIZATION"
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
  	4,0,17,173,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,1,0,4,0,39,8,0,11,0,12,0,40,1,0,1,
  	0,1,1,5,1,46,8,1,10,1,12,1,49,9,1,1,1,1,1,1,1,1,1,5,1,55,8,1,10,1,12,
  	1,58,9,1,1,1,1,1,1,2,5,2,63,8,2,10,2,12,2,66,9,2,1,2,1,2,1,2,1,2,1,2,
  	5,2,73,8,2,10,2,12,2,76,9,2,1,2,1,2,1,2,1,2,1,2,1,3,5,3,84,8,3,10,3,12,
  	3,87,9,3,1,3,1,3,5,3,91,8,3,10,3,12,3,94,9,3,1,3,1,3,1,4,1,4,1,4,1,4,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,109,8,5,10,5,12,5,112,9,5,1,5,1,5,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,4,7,132,8,
  	7,11,7,12,7,133,1,7,1,7,1,8,4,8,139,8,8,11,8,12,8,140,1,8,1,8,1,9,1,9,
  	1,10,1,10,1,11,4,11,150,8,11,11,11,12,11,151,1,12,1,12,1,13,1,13,1,13,
  	1,13,1,14,1,14,1,14,1,14,1,15,4,15,165,8,15,11,15,12,15,166,1,16,1,16,
  	1,16,1,16,1,16,2,74,133,0,17,3,1,5,2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,
  	21,10,23,11,25,12,27,13,29,14,31,15,33,16,35,17,3,0,1,2,5,2,0,9,9,32,
  	32,3,0,9,10,13,13,32,32,2,0,10,10,13,13,6,0,9,9,32,32,40,41,44,44,59,
  	59,61,61,1,0,59,59,183,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,
  	0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,1,19,1,0,0,0,1,
  	21,1,0,0,0,1,23,1,0,0,0,1,25,1,0,0,0,1,27,1,0,0,0,1,29,1,0,0,0,1,31,1,
  	0,0,0,2,33,1,0,0,0,2,35,1,0,0,0,3,38,1,0,0,0,5,47,1,0,0,0,7,64,1,0,0,
  	0,9,85,1,0,0,0,11,97,1,0,0,0,13,101,1,0,0,0,15,115,1,0,0,0,17,131,1,0,
  	0,0,19,138,1,0,0,0,21,144,1,0,0,0,23,146,1,0,0,0,25,149,1,0,0,0,27,153,
  	1,0,0,0,29,155,1,0,0,0,31,159,1,0,0,0,33,164,1,0,0,0,35,168,1,0,0,0,37,
  	39,7,0,0,0,38,37,1,0,0,0,39,40,1,0,0,0,40,38,1,0,0,0,40,41,1,0,0,0,41,
  	42,1,0,0,0,42,43,6,0,0,0,43,4,1,0,0,0,44,46,7,1,0,0,45,44,1,0,0,0,46,
  	49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,50,1,0,0,0,49,47,1,0,0,0,50,
  	51,5,47,0,0,51,52,5,47,0,0,52,56,1,0,0,0,53,55,8,2,0,0,54,53,1,0,0,0,
  	55,58,1,0,0,0,56,54,1,0,0,0,56,57,1,0,0,0,57,59,1,0,0,0,58,56,1,0,0,0,
  	59,60,6,1,0,0,60,6,1,0,0,0,61,63,7,1,0,0,62,61,1,0,0,0,63,66,1,0,0,0,
  	64,62,1,0,0,0,64,65,1,0,0,0,65,67,1,0,0,0,66,64,1,0,0,0,67,68,5,47,0,
  	0,68,69,5,42,0,0,69,74,1,0,0,0,70,73,7,1,0,0,71,73,9,0,0,0,72,70,1,0,
  	0,0,72,71,1,0,0,0,73,76,1,0,0,0,74,75,1,0,0,0,74,72,1,0,0,0,75,77,1,0,
  	0,0,76,74,1,0,0,0,77,78,5,42,0,0,78,79,5,47,0,0,79,80,1,0,0,0,80,81,6,
  	2,0,0,81,8,1,0,0,0,82,84,7,1,0,0,83,82,1,0,0,0,84,87,1,0,0,0,85,83,1,
  	0,0,0,85,86,1,0,0,0,86,88,1,0,0,0,87,85,1,0,0,0,88,92,5,35,0,0,89,91,
  	8,2,0,0,90,89,1,0,0,0,91,94,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,95,
  	1,0,0,0,94,92,1,0,0,0,95,96,6,3,0,0,96,10,1,0,0,0,97,98,7,2,0,0,98,99,
  	1,0,0,0,99,100,6,4,0,0,100,12,1,0,0,0,101,102,5,73,0,0,102,103,5,77,0,
  	0,103,104,5,71,0,0,104,105,5,85,0,0,105,106,5,73,0,0,106,110,1,0,0,0,
  	107,109,3,3,0,0,108,107,1,0,0,0,109,112,1,0,0,0,110,108,1,0,0,0,110,111,
  	1,0,0,0,111,113,1,0,0,0,112,110,1,0,0,0,113,114,6,5,1,0,114,14,1,0,0,
  	0,115,116,5,73,0,0,116,117,5,77,0,0,117,118,5,71,0,0,118,119,5,85,0,0,
  	119,120,5,73,0,0,120,121,5,95,0,0,121,122,5,82,0,0,122,123,5,65,0,0,123,
  	124,5,78,0,0,124,125,5,71,0,0,125,126,5,69,0,0,126,127,5,68,0,0,127,128,
  	1,0,0,0,128,129,6,6,1,0,129,16,1,0,0,0,130,132,9,0,0,0,131,130,1,0,0,
  	0,132,133,1,0,0,0,133,134,1,0,0,0,133,131,1,0,0,0,134,135,1,0,0,0,135,
  	136,6,7,0,0,136,18,1,0,0,0,137,139,7,0,0,0,138,137,1,0,0,0,139,140,1,
  	0,0,0,140,138,1,0,0,0,140,141,1,0,0,0,141,142,1,0,0,0,142,143,6,8,0,0,
  	143,20,1,0,0,0,144,145,5,40,0,0,145,22,1,0,0,0,146,147,5,41,0,0,147,24,
  	1,0,0,0,148,150,8,3,0,0,149,148,1,0,0,0,150,151,1,0,0,0,151,149,1,0,0,
  	0,151,152,1,0,0,0,152,26,1,0,0,0,153,154,5,44,0,0,154,28,1,0,0,0,155,
  	156,5,61,0,0,156,157,1,0,0,0,157,158,6,13,2,0,158,30,1,0,0,0,159,160,
  	5,59,0,0,160,161,1,0,0,0,161,162,6,14,3,0,162,32,1,0,0,0,163,165,8,4,
  	0,0,164,163,1,0,0,0,165,166,1,0,0,0,166,164,1,0,0,0,166,167,1,0,0,0,167,
  	34,1,0,0,0,168,169,5,59,0,0,169,170,1,0,0,0,170,171,6,16,3,0,171,172,
  	6,16,3,0,172,36,1,0,0,0,16,0,1,2,40,47,56,64,72,74,85,92,110,133,140,
  	151,166,4,6,0,0,5,1,0,5,2,0,4,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  imguipplexerLexerStaticData = staticData.release();
}

}

ImguiPPLexer::ImguiPPLexer(CharStream *input) : Lexer(input) {
  ImguiPPLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *imguipplexerLexerStaticData->atn, imguipplexerLexerStaticData->decisionToDFA, imguipplexerLexerStaticData->sharedContextCache);
}

ImguiPPLexer::~ImguiPPLexer() {
  delete _interpreter;
}

std::string ImguiPPLexer::getGrammarFileName() const {
  return "ImguiPPLexer.g4";
}

const std::vector<std::string>& ImguiPPLexer::getRuleNames() const {
  return imguipplexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ImguiPPLexer::getChannelNames() const {
  return imguipplexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ImguiPPLexer::getModeNames() const {
  return imguipplexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ImguiPPLexer::getVocabulary() const {
  return imguipplexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ImguiPPLexer::getSerializedATN() const {
  return imguipplexerLexerStaticData->serializedATN;
}

const atn::ATN& ImguiPPLexer::getATN() const {
  return *imguipplexerLexerStaticData->atn;
}




void ImguiPPLexer::initialize() {
  std::call_once(imguipplexerLexerOnceFlag, imguipplexerLexerInitialize);
}
