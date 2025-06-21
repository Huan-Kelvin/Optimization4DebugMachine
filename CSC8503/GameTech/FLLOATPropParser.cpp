
// Generated from antlr4/FLLOATProp.g by ANTLR 4.9.1


#include "FLLOATPropListener.h"
#include "FLLOATPropVisitor.h"

#include "FLLOATPropParser.h"


using namespace antlrcpp;
using namespace antlr4;

FLLOATPropParser::FLLOATPropParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

FLLOATPropParser::~FLLOATPropParser() {
  delete _interpreter;
}

std::string FLLOATPropParser::getGrammarFileName() const {
  return "FLLOATProp.g";
}

const std::vector<std::string>& FLLOATPropParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& FLLOATPropParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StatementContext ------------------------------------------------------------------

FLLOATPropParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t FLLOATPropParser::StatementContext::getRuleIndex() const {
  return FLLOATPropParser::RuleStatement;
}

void FLLOATPropParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NegationContext ------------------------------------------------------------------

FLLOATPropParser::StatementContext* FLLOATPropParser::NegationContext::statement() {
  return getRuleContext<FLLOATPropParser::StatementContext>(0);
}

FLLOATPropParser::NegationContext::NegationContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::NegationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegation(this);
}
void FLLOATPropParser::NegationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegation(this);
}

antlrcpp::Any FLLOATPropParser::NegationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitNegation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenContext ------------------------------------------------------------------

FLLOATPropParser::StatementContext* FLLOATPropParser::ParenContext::statement() {
  return getRuleContext<FLLOATPropParser::StatementContext>(0);
}

FLLOATPropParser::ParenContext::ParenContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::ParenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParen(this);
}
void FLLOATPropParser::ParenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParen(this);
}

antlrcpp::Any FLLOATPropParser::ParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrContext ------------------------------------------------------------------

std::vector<FLLOATPropParser::StatementContext *> FLLOATPropParser::OrContext::statement() {
  return getRuleContexts<FLLOATPropParser::StatementContext>();
}

FLLOATPropParser::StatementContext* FLLOATPropParser::OrContext::statement(size_t i) {
  return getRuleContext<FLLOATPropParser::StatementContext>(i);
}

FLLOATPropParser::OrContext::OrContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::OrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr(this);
}
void FLLOATPropParser::OrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr(this);
}

antlrcpp::Any FLLOATPropParser::OrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TopContext ------------------------------------------------------------------

FLLOATPropParser::TopContext::TopContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::TopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTop(this);
}
void FLLOATPropParser::TopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTop(this);
}

antlrcpp::Any FLLOATPropParser::TopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitTop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BotContext ------------------------------------------------------------------

FLLOATPropParser::BotContext::BotContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::BotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBot(this);
}
void FLLOATPropParser::BotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBot(this);
}

antlrcpp::Any FLLOATPropParser::BotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitBot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndContext ------------------------------------------------------------------

std::vector<FLLOATPropParser::StatementContext *> FLLOATPropParser::AndContext::statement() {
  return getRuleContexts<FLLOATPropParser::StatementContext>();
}

FLLOATPropParser::StatementContext* FLLOATPropParser::AndContext::statement(size_t i) {
  return getRuleContext<FLLOATPropParser::StatementContext>(i);
}

FLLOATPropParser::AndContext::AndContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::AndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnd(this);
}
void FLLOATPropParser::AndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnd(this);
}

antlrcpp::Any FLLOATPropParser::AndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AtomContext ------------------------------------------------------------------

tree::TerminalNode* FLLOATPropParser::AtomContext::ID() {
  return getToken(FLLOATPropParser::ID, 0);
}

FLLOATPropParser::AtomContext::AtomContext(StatementContext *ctx) { copyFrom(ctx); }

void FLLOATPropParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}
void FLLOATPropParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FLLOATPropListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}

antlrcpp::Any FLLOATPropParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FLLOATPropVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

FLLOATPropParser::StatementContext* FLLOATPropParser::statement() {
   return statement(0);
}

FLLOATPropParser::StatementContext* FLLOATPropParser::statement(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  FLLOATPropParser::StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, parentState);
  FLLOATPropParser::StatementContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, FLLOATPropParser::RuleStatement, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(12);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case FLLOATPropParser::T__0: {
        _localctx = _tracker.createInstance<NegationContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(3);
        match(FLLOATPropParser::T__0);
        setState(4);
        statement(7);
        break;
      }

      case FLLOATPropParser::ID: {
        _localctx = _tracker.createInstance<AtomContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(5);
        match(FLLOATPropParser::ID);
        break;
      }

      case FLLOATPropParser::T__1: {
        _localctx = _tracker.createInstance<ParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(6);
        match(FLLOATPropParser::T__1);
        setState(7);
        statement(0);
        setState(8);
        match(FLLOATPropParser::T__2);
        break;
      }

      case FLLOATPropParser::T__5: {
        _localctx = _tracker.createInstance<TopContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(10);
        match(FLLOATPropParser::T__5);
        break;
      }

      case FLLOATPropParser::T__6: {
        _localctx = _tracker.createInstance<BotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(11);
        match(FLLOATPropParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(22);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(20);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AndContext>(_tracker.createInstance<StatementContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleStatement);
          setState(14);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(15);
          match(FLLOATPropParser::T__3);
          setState(16);
          statement(4);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OrContext>(_tracker.createInstance<StatementContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleStatement);
          setState(17);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(18);
          match(FLLOATPropParser::T__4);
          setState(19);
          statement(3);
          break;
        }

        default:
          break;
        } 
      }
      setState(24);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool FLLOATPropParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return statementSempred(dynamic_cast<StatementContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool FLLOATPropParser::statementSempred(StatementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> FLLOATPropParser::_decisionToDFA;
atn::PredictionContextCache FLLOATPropParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FLLOATPropParser::_atn;
std::vector<uint16_t> FLLOATPropParser::_serializedATN;

std::vector<std::string> FLLOATPropParser::_ruleNames = {
  "statement"
};

std::vector<std::string> FLLOATPropParser::_literalNames = {
  "", "'~'", "'('", "')'", "'&'", "'|'", "'True'", "'False'"
};

std::vector<std::string> FLLOATPropParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "NUMBER", "ID", "WS"
};

dfa::Vocabulary FLLOATPropParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> FLLOATPropParser::_tokenNames;

FLLOATPropParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0xc, 0x1c, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x5, 0x2, 0xf, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x17, 0xa, 0x2, 0xc, 0x2, 0xe, 
       0x2, 0x1a, 0xb, 0x2, 0x3, 0x2, 0x2, 0x3, 0x2, 0x3, 0x2, 0x2, 0x2, 
       0x2, 0x20, 0x2, 0xe, 0x3, 0x2, 0x2, 0x2, 0x4, 0x5, 0x8, 0x2, 0x1, 
       0x2, 0x5, 0x6, 0x7, 0x3, 0x2, 0x2, 0x6, 0xf, 0x5, 0x2, 0x2, 0x9, 
       0x7, 0xf, 0x7, 0xb, 0x2, 0x2, 0x8, 0x9, 0x7, 0x4, 0x2, 0x2, 0x9, 
       0xa, 0x5, 0x2, 0x2, 0x2, 0xa, 0xb, 0x7, 0x5, 0x2, 0x2, 0xb, 0xf, 
       0x3, 0x2, 0x2, 0x2, 0xc, 0xf, 0x7, 0x8, 0x2, 0x2, 0xd, 0xf, 0x7, 
       0x9, 0x2, 0x2, 0xe, 0x4, 0x3, 0x2, 0x2, 0x2, 0xe, 0x7, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x8, 0x3, 0x2, 0x2, 0x2, 0xe, 0xc, 0x3, 0x2, 0x2, 
       0x2, 0xe, 0xd, 0x3, 0x2, 0x2, 0x2, 0xf, 0x18, 0x3, 0x2, 0x2, 0x2, 
       0x10, 0x11, 0xc, 0x6, 0x2, 0x2, 0x11, 0x12, 0x7, 0x6, 0x2, 0x2, 0x12, 
       0x17, 0x5, 0x2, 0x2, 0x6, 0x13, 0x14, 0xc, 0x5, 0x2, 0x2, 0x14, 0x15, 
       0x7, 0x7, 0x2, 0x2, 0x15, 0x17, 0x5, 0x2, 0x2, 0x5, 0x16, 0x10, 0x3, 
       0x2, 0x2, 0x2, 0x16, 0x13, 0x3, 0x2, 0x2, 0x2, 0x17, 0x1a, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x16, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 
       0x2, 0x19, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 
       0x5, 0xe, 0x16, 0x18, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

FLLOATPropParser::Initializer FLLOATPropParser::_init;
