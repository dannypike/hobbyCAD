
// Generated from /home/dan/Projects/hobbyCAD/grammar/OpenSCAD.g4 by ANTLR 4.13.2


#include "OpenSCADVisitor.h"

#include "OpenSCADParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct OpenSCADParserStaticData final {
  OpenSCADParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  OpenSCADParserStaticData(const OpenSCADParserStaticData&) = delete;
  OpenSCADParserStaticData(OpenSCADParserStaticData&&) = delete;
  OpenSCADParserStaticData& operator=(const OpenSCADParserStaticData&) = delete;
  OpenSCADParserStaticData& operator=(OpenSCADParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag openscadParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<OpenSCADParserStaticData> openscadParserStaticData = nullptr;

void openscadParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (openscadParserStaticData != nullptr) {
    return;
  }
#else
  assert(openscadParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<OpenSCADParserStaticData>(
    std::vector<std::string>{
      "file", "statement", "functionCall", "argumentList", "argument", "expression", 
      "boolLiteral", "vector"
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
  	4,1,14,67,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,1,0,5,0,18,8,0,10,0,12,0,21,9,0,1,0,1,0,1,1,1,1,1,1,1,2,1,2,1,2,3,
  	2,31,8,2,1,2,1,2,1,3,1,3,1,3,5,3,38,8,3,10,3,12,3,41,9,3,1,4,1,4,1,4,
  	1,4,3,4,47,8,4,1,5,1,5,1,5,3,5,52,8,5,1,6,1,6,1,7,1,7,1,7,1,7,5,7,60,
  	8,7,10,7,12,7,63,9,7,1,7,1,7,1,7,0,0,8,0,2,4,6,8,10,12,14,0,1,1,0,1,2,
  	65,0,19,1,0,0,0,2,24,1,0,0,0,4,27,1,0,0,0,6,34,1,0,0,0,8,46,1,0,0,0,10,
  	51,1,0,0,0,12,53,1,0,0,0,14,55,1,0,0,0,16,18,3,2,1,0,17,16,1,0,0,0,18,
  	21,1,0,0,0,19,17,1,0,0,0,19,20,1,0,0,0,20,22,1,0,0,0,21,19,1,0,0,0,22,
  	23,5,0,0,1,23,1,1,0,0,0,24,25,3,4,2,0,25,26,5,5,0,0,26,3,1,0,0,0,27,28,
  	5,3,0,0,28,30,5,7,0,0,29,31,3,6,3,0,30,29,1,0,0,0,30,31,1,0,0,0,31,32,
  	1,0,0,0,32,33,5,8,0,0,33,5,1,0,0,0,34,39,3,8,4,0,35,36,5,6,0,0,36,38,
  	3,8,4,0,37,35,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,7,
  	1,0,0,0,41,39,1,0,0,0,42,43,5,3,0,0,43,44,5,11,0,0,44,47,3,10,5,0,45,
  	47,3,10,5,0,46,42,1,0,0,0,46,45,1,0,0,0,47,9,1,0,0,0,48,52,5,4,0,0,49,
  	52,3,12,6,0,50,52,3,14,7,0,51,48,1,0,0,0,51,49,1,0,0,0,51,50,1,0,0,0,
  	52,11,1,0,0,0,53,54,7,0,0,0,54,13,1,0,0,0,55,56,5,9,0,0,56,61,3,10,5,
  	0,57,58,5,6,0,0,58,60,3,10,5,0,59,57,1,0,0,0,60,63,1,0,0,0,61,59,1,0,
  	0,0,61,62,1,0,0,0,62,64,1,0,0,0,63,61,1,0,0,0,64,65,5,10,0,0,65,15,1,
  	0,0,0,6,19,30,39,46,51,61
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  openscadParserStaticData = std::move(staticData);
}

}

OpenSCADParser::OpenSCADParser(TokenStream *input) : OpenSCADParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

OpenSCADParser::OpenSCADParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  OpenSCADParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *openscadParserStaticData->atn, openscadParserStaticData->decisionToDFA, openscadParserStaticData->sharedContextCache, options);
}

OpenSCADParser::~OpenSCADParser() {
  delete _interpreter;
}

const atn::ATN& OpenSCADParser::getATN() const {
  return *openscadParserStaticData->atn;
}

std::string OpenSCADParser::getGrammarFileName() const {
  return "OpenSCAD.g4";
}

const std::vector<std::string>& OpenSCADParser::getRuleNames() const {
  return openscadParserStaticData->ruleNames;
}

const dfa::Vocabulary& OpenSCADParser::getVocabulary() const {
  return openscadParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView OpenSCADParser::getSerializedATN() const {
  return openscadParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

OpenSCADParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* OpenSCADParser::FileContext::EOF() {
  return getToken(OpenSCADParser::EOF, 0);
}

std::vector<OpenSCADParser::StatementContext *> OpenSCADParser::FileContext::statement() {
  return getRuleContexts<OpenSCADParser::StatementContext>();
}

OpenSCADParser::StatementContext* OpenSCADParser::FileContext::statement(size_t i) {
  return getRuleContext<OpenSCADParser::StatementContext>(i);
}


size_t OpenSCADParser::FileContext::getRuleIndex() const {
  return OpenSCADParser::RuleFile;
}


std::any OpenSCADParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::FileContext* OpenSCADParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, OpenSCADParser::RuleFile);
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
    setState(19);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OpenSCADParser::ID) {
      setState(16);
      statement();
      setState(21);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(22);
    match(OpenSCADParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

OpenSCADParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

OpenSCADParser::FunctionCallContext* OpenSCADParser::StatementContext::functionCall() {
  return getRuleContext<OpenSCADParser::FunctionCallContext>(0);
}

tree::TerminalNode* OpenSCADParser::StatementContext::SEMI() {
  return getToken(OpenSCADParser::SEMI, 0);
}


size_t OpenSCADParser::StatementContext::getRuleIndex() const {
  return OpenSCADParser::RuleStatement;
}


std::any OpenSCADParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::StatementContext* OpenSCADParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, OpenSCADParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(24);
    functionCall();
    setState(25);
    match(OpenSCADParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

OpenSCADParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* OpenSCADParser::FunctionCallContext::ID() {
  return getToken(OpenSCADParser::ID, 0);
}

tree::TerminalNode* OpenSCADParser::FunctionCallContext::LPAREN() {
  return getToken(OpenSCADParser::LPAREN, 0);
}

tree::TerminalNode* OpenSCADParser::FunctionCallContext::RPAREN() {
  return getToken(OpenSCADParser::RPAREN, 0);
}

OpenSCADParser::ArgumentListContext* OpenSCADParser::FunctionCallContext::argumentList() {
  return getRuleContext<OpenSCADParser::ArgumentListContext>(0);
}


size_t OpenSCADParser::FunctionCallContext::getRuleIndex() const {
  return OpenSCADParser::RuleFunctionCall;
}


std::any OpenSCADParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::FunctionCallContext* OpenSCADParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 4, OpenSCADParser::RuleFunctionCall);
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
    setState(27);
    match(OpenSCADParser::ID);
    setState(28);
    match(OpenSCADParser::LPAREN);
    setState(30);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 542) != 0)) {
      setState(29);
      argumentList();
    }
    setState(32);
    match(OpenSCADParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

OpenSCADParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<OpenSCADParser::ArgumentContext *> OpenSCADParser::ArgumentListContext::argument() {
  return getRuleContexts<OpenSCADParser::ArgumentContext>();
}

OpenSCADParser::ArgumentContext* OpenSCADParser::ArgumentListContext::argument(size_t i) {
  return getRuleContext<OpenSCADParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> OpenSCADParser::ArgumentListContext::COMMA() {
  return getTokens(OpenSCADParser::COMMA);
}

tree::TerminalNode* OpenSCADParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(OpenSCADParser::COMMA, i);
}


size_t OpenSCADParser::ArgumentListContext::getRuleIndex() const {
  return OpenSCADParser::RuleArgumentList;
}


std::any OpenSCADParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::ArgumentListContext* OpenSCADParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 6, OpenSCADParser::RuleArgumentList);
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
    setState(34);
    argument();
    setState(39);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OpenSCADParser::COMMA) {
      setState(35);
      match(OpenSCADParser::COMMA);
      setState(36);
      argument();
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

OpenSCADParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t OpenSCADParser::ArgumentContext::getRuleIndex() const {
  return OpenSCADParser::RuleArgument;
}

void OpenSCADParser::ArgumentContext::copyFrom(ArgumentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PositionalArgContext ------------------------------------------------------------------

OpenSCADParser::ExpressionContext* OpenSCADParser::PositionalArgContext::expression() {
  return getRuleContext<OpenSCADParser::ExpressionContext>(0);
}

OpenSCADParser::PositionalArgContext::PositionalArgContext(ArgumentContext *ctx) { copyFrom(ctx); }


std::any OpenSCADParser::PositionalArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitPositionalArg(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NamedArgContext ------------------------------------------------------------------

tree::TerminalNode* OpenSCADParser::NamedArgContext::ID() {
  return getToken(OpenSCADParser::ID, 0);
}

tree::TerminalNode* OpenSCADParser::NamedArgContext::EQUALS() {
  return getToken(OpenSCADParser::EQUALS, 0);
}

OpenSCADParser::ExpressionContext* OpenSCADParser::NamedArgContext::expression() {
  return getRuleContext<OpenSCADParser::ExpressionContext>(0);
}

OpenSCADParser::NamedArgContext::NamedArgContext(ArgumentContext *ctx) { copyFrom(ctx); }


std::any OpenSCADParser::NamedArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitNamedArg(this);
  else
    return visitor->visitChildren(this);
}
OpenSCADParser::ArgumentContext* OpenSCADParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 8, OpenSCADParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(46);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OpenSCADParser::ID: {
        _localctx = _tracker.createInstance<OpenSCADParser::NamedArgContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(42);
        match(OpenSCADParser::ID);
        setState(43);
        match(OpenSCADParser::EQUALS);
        setState(44);
        expression();
        break;
      }

      case OpenSCADParser::TRUE:
      case OpenSCADParser::FALSE:
      case OpenSCADParser::NUMBER:
      case OpenSCADParser::LBRACKET: {
        _localctx = _tracker.createInstance<OpenSCADParser::PositionalArgContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(45);
        expression();
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

//----------------- ExpressionContext ------------------------------------------------------------------

OpenSCADParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t OpenSCADParser::ExpressionContext::getRuleIndex() const {
  return OpenSCADParser::RuleExpression;
}

void OpenSCADParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolExprContext ------------------------------------------------------------------

OpenSCADParser::BoolLiteralContext* OpenSCADParser::BoolExprContext::boolLiteral() {
  return getRuleContext<OpenSCADParser::BoolLiteralContext>(0);
}

OpenSCADParser::BoolExprContext::BoolExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any OpenSCADParser::BoolExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitBoolExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberExprContext ------------------------------------------------------------------

tree::TerminalNode* OpenSCADParser::NumberExprContext::NUMBER() {
  return getToken(OpenSCADParser::NUMBER, 0);
}

OpenSCADParser::NumberExprContext::NumberExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any OpenSCADParser::NumberExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitNumberExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorExprContext ------------------------------------------------------------------

OpenSCADParser::VectorContext* OpenSCADParser::VectorExprContext::vector() {
  return getRuleContext<OpenSCADParser::VectorContext>(0);
}

OpenSCADParser::VectorExprContext::VectorExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any OpenSCADParser::VectorExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitVectorExpr(this);
  else
    return visitor->visitChildren(this);
}
OpenSCADParser::ExpressionContext* OpenSCADParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 10, OpenSCADParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(51);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OpenSCADParser::NUMBER: {
        _localctx = _tracker.createInstance<OpenSCADParser::NumberExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(48);
        match(OpenSCADParser::NUMBER);
        break;
      }

      case OpenSCADParser::TRUE:
      case OpenSCADParser::FALSE: {
        _localctx = _tracker.createInstance<OpenSCADParser::BoolExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(49);
        boolLiteral();
        break;
      }

      case OpenSCADParser::LBRACKET: {
        _localctx = _tracker.createInstance<OpenSCADParser::VectorExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(50);
        vector();
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

//----------------- BoolLiteralContext ------------------------------------------------------------------

OpenSCADParser::BoolLiteralContext::BoolLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* OpenSCADParser::BoolLiteralContext::TRUE() {
  return getToken(OpenSCADParser::TRUE, 0);
}

tree::TerminalNode* OpenSCADParser::BoolLiteralContext::FALSE() {
  return getToken(OpenSCADParser::FALSE, 0);
}


size_t OpenSCADParser::BoolLiteralContext::getRuleIndex() const {
  return OpenSCADParser::RuleBoolLiteral;
}


std::any OpenSCADParser::BoolLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitBoolLiteral(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::BoolLiteralContext* OpenSCADParser::boolLiteral() {
  BoolLiteralContext *_localctx = _tracker.createInstance<BoolLiteralContext>(_ctx, getState());
  enterRule(_localctx, 12, OpenSCADParser::RuleBoolLiteral);
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
    setState(53);
    _la = _input->LA(1);
    if (!(_la == OpenSCADParser::TRUE

    || _la == OpenSCADParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VectorContext ------------------------------------------------------------------

OpenSCADParser::VectorContext::VectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* OpenSCADParser::VectorContext::LBRACKET() {
  return getToken(OpenSCADParser::LBRACKET, 0);
}

std::vector<OpenSCADParser::ExpressionContext *> OpenSCADParser::VectorContext::expression() {
  return getRuleContexts<OpenSCADParser::ExpressionContext>();
}

OpenSCADParser::ExpressionContext* OpenSCADParser::VectorContext::expression(size_t i) {
  return getRuleContext<OpenSCADParser::ExpressionContext>(i);
}

tree::TerminalNode* OpenSCADParser::VectorContext::RBRACKET() {
  return getToken(OpenSCADParser::RBRACKET, 0);
}

std::vector<tree::TerminalNode *> OpenSCADParser::VectorContext::COMMA() {
  return getTokens(OpenSCADParser::COMMA);
}

tree::TerminalNode* OpenSCADParser::VectorContext::COMMA(size_t i) {
  return getToken(OpenSCADParser::COMMA, i);
}


size_t OpenSCADParser::VectorContext::getRuleIndex() const {
  return OpenSCADParser::RuleVector;
}


std::any OpenSCADParser::VectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OpenSCADVisitor*>(visitor))
    return parserVisitor->visitVector(this);
  else
    return visitor->visitChildren(this);
}

OpenSCADParser::VectorContext* OpenSCADParser::vector() {
  VectorContext *_localctx = _tracker.createInstance<VectorContext>(_ctx, getState());
  enterRule(_localctx, 14, OpenSCADParser::RuleVector);
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
    setState(55);
    match(OpenSCADParser::LBRACKET);
    setState(56);
    expression();
    setState(61);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OpenSCADParser::COMMA) {
      setState(57);
      match(OpenSCADParser::COMMA);
      setState(58);
      expression();
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(64);
    match(OpenSCADParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void OpenSCADParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  openscadParserInitialize();
#else
  ::antlr4::internal::call_once(openscadParserOnceFlag, openscadParserInitialize);
#endif
}
