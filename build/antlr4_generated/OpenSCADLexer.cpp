
// Generated from /home/dan/Projects/hobbyCAD/grammar/OpenSCAD.g4 by ANTLR 4.13.2


#include "OpenSCADLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct OpenSCADLexerStaticData final {
  OpenSCADLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  OpenSCADLexerStaticData(const OpenSCADLexerStaticData&) = delete;
  OpenSCADLexerStaticData(OpenSCADLexerStaticData&&) = delete;
  OpenSCADLexerStaticData& operator=(const OpenSCADLexerStaticData&) = delete;
  OpenSCADLexerStaticData& operator=(OpenSCADLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag openscadlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<OpenSCADLexerStaticData> openscadlexerLexerStaticData = nullptr;

void openscadlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (openscadlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(openscadlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<OpenSCADLexerStaticData>(
    std::vector<std::string>{
      "TRUE", "FALSE", "ID", "NUMBER", "SEMI", "COMMA", "LPAREN", "RPAREN", 
      "LBRACKET", "RBRACKET", "EQUALS", "LINE_COMMENT", "BLOCK_COMMENT", 
      "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'true'", "'false'", "", "", "';'", "','", "'('", "')'", "'['", 
      "']'", "'='"
    },
    std::vector<std::string>{
      "", "TRUE", "FALSE", "ID", "NUMBER", "SEMI", "COMMA", "LPAREN", "RPAREN", 
      "LBRACKET", "RBRACKET", "EQUALS", "LINE_COMMENT", "BLOCK_COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,14,121,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,
  	1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,5,2,43,8,2,10,2,12,2,
  	46,9,2,1,3,3,3,49,8,3,1,3,4,3,52,8,3,11,3,12,3,53,1,3,1,3,5,3,58,8,3,
  	10,3,12,3,61,9,3,3,3,63,8,3,1,3,1,3,3,3,67,8,3,1,3,4,3,70,8,3,11,3,12,
  	3,71,3,3,74,8,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,
  	1,10,1,11,1,11,1,11,1,11,5,11,94,8,11,10,11,12,11,97,9,11,1,11,1,11,1,
  	12,1,12,1,12,1,12,5,12,105,8,12,10,12,12,12,108,9,12,1,12,1,12,1,12,1,
  	12,1,12,1,13,4,13,116,8,13,11,13,12,13,117,1,13,1,13,1,106,0,14,1,1,3,
  	2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,1,0,7,
  	3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,48,57,2,0,69,
  	69,101,101,2,0,43,43,45,45,2,0,10,10,13,13,3,0,9,10,13,13,32,32,131,0,
  	1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
  	0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,
  	23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,1,29,1,0,0,0,3,34,1,0,0,0,5,40,1,
  	0,0,0,7,48,1,0,0,0,9,75,1,0,0,0,11,77,1,0,0,0,13,79,1,0,0,0,15,81,1,0,
  	0,0,17,83,1,0,0,0,19,85,1,0,0,0,21,87,1,0,0,0,23,89,1,0,0,0,25,100,1,
  	0,0,0,27,115,1,0,0,0,29,30,5,116,0,0,30,31,5,114,0,0,31,32,5,117,0,0,
  	32,33,5,101,0,0,33,2,1,0,0,0,34,35,5,102,0,0,35,36,5,97,0,0,36,37,5,108,
  	0,0,37,38,5,115,0,0,38,39,5,101,0,0,39,4,1,0,0,0,40,44,7,0,0,0,41,43,
  	7,1,0,0,42,41,1,0,0,0,43,46,1,0,0,0,44,42,1,0,0,0,44,45,1,0,0,0,45,6,
  	1,0,0,0,46,44,1,0,0,0,47,49,5,45,0,0,48,47,1,0,0,0,48,49,1,0,0,0,49,51,
  	1,0,0,0,50,52,7,2,0,0,51,50,1,0,0,0,52,53,1,0,0,0,53,51,1,0,0,0,53,54,
  	1,0,0,0,54,62,1,0,0,0,55,59,5,46,0,0,56,58,7,2,0,0,57,56,1,0,0,0,58,61,
  	1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,63,1,0,0,0,61,59,1,0,0,0,62,55,
  	1,0,0,0,62,63,1,0,0,0,63,73,1,0,0,0,64,66,7,3,0,0,65,67,7,4,0,0,66,65,
  	1,0,0,0,66,67,1,0,0,0,67,69,1,0,0,0,68,70,7,2,0,0,69,68,1,0,0,0,70,71,
  	1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,64,1,0,0,0,73,74,
  	1,0,0,0,74,8,1,0,0,0,75,76,5,59,0,0,76,10,1,0,0,0,77,78,5,44,0,0,78,12,
  	1,0,0,0,79,80,5,40,0,0,80,14,1,0,0,0,81,82,5,41,0,0,82,16,1,0,0,0,83,
  	84,5,91,0,0,84,18,1,0,0,0,85,86,5,93,0,0,86,20,1,0,0,0,87,88,5,61,0,0,
  	88,22,1,0,0,0,89,90,5,47,0,0,90,91,5,47,0,0,91,95,1,0,0,0,92,94,8,5,0,
  	0,93,92,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,
  	0,97,95,1,0,0,0,98,99,6,11,0,0,99,24,1,0,0,0,100,101,5,47,0,0,101,102,
  	5,42,0,0,102,106,1,0,0,0,103,105,9,0,0,0,104,103,1,0,0,0,105,108,1,0,
  	0,0,106,107,1,0,0,0,106,104,1,0,0,0,107,109,1,0,0,0,108,106,1,0,0,0,109,
  	110,5,42,0,0,110,111,5,47,0,0,111,112,1,0,0,0,112,113,6,12,0,0,113,26,
  	1,0,0,0,114,116,7,6,0,0,115,114,1,0,0,0,116,117,1,0,0,0,117,115,1,0,0,
  	0,117,118,1,0,0,0,118,119,1,0,0,0,119,120,6,13,0,0,120,28,1,0,0,0,12,
  	0,44,48,53,59,62,66,71,73,95,106,117,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  openscadlexerLexerStaticData = std::move(staticData);
}

}

OpenSCADLexer::OpenSCADLexer(CharStream *input) : Lexer(input) {
  OpenSCADLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *openscadlexerLexerStaticData->atn, openscadlexerLexerStaticData->decisionToDFA, openscadlexerLexerStaticData->sharedContextCache);
}

OpenSCADLexer::~OpenSCADLexer() {
  delete _interpreter;
}

std::string OpenSCADLexer::getGrammarFileName() const {
  return "OpenSCAD.g4";
}

const std::vector<std::string>& OpenSCADLexer::getRuleNames() const {
  return openscadlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& OpenSCADLexer::getChannelNames() const {
  return openscadlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& OpenSCADLexer::getModeNames() const {
  return openscadlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& OpenSCADLexer::getVocabulary() const {
  return openscadlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView OpenSCADLexer::getSerializedATN() const {
  return openscadlexerLexerStaticData->serializedATN;
}

const atn::ATN& OpenSCADLexer::getATN() const {
  return *openscadlexerLexerStaticData->atn;
}




void OpenSCADLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  openscadlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(openscadlexerLexerOnceFlag, openscadlexerLexerInitialize);
#endif
}
