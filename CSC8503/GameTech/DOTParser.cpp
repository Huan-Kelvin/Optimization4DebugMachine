
// Generated from src/knobab/flloat_deps/DOT.g by ANTLR 4.9.3


#include "DOTListener.h"
#include "DOTVisitor.h"

#include "DOTParser.h"


using namespace antlrcpp;
using namespace antlr4;

DOTParser::DOTParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

DOTParser::~DOTParser() {
  delete _interpreter;
}

std::string DOTParser::getGrammarFileName() const {
  return "DOT.g";
}

const std::vector<std::string>& DOTParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& DOTParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- GraphContext ------------------------------------------------------------------

DOTParser::GraphContext::GraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::Stmt_listContext* DOTParser::GraphContext::stmt_list() {
  return getRuleContext<DOTParser::Stmt_listContext>(0);
}

tree::TerminalNode* DOTParser::GraphContext::GRAPH() {
  return getToken(DOTParser::GRAPH, 0);
}

tree::TerminalNode* DOTParser::GraphContext::DIGRAPH() {
  return getToken(DOTParser::DIGRAPH, 0);
}

tree::TerminalNode* DOTParser::GraphContext::STRICT() {
  return getToken(DOTParser::STRICT, 0);
}

DOTParser::IdContext* DOTParser::GraphContext::id() {
  return getRuleContext<DOTParser::IdContext>(0);
}


size_t DOTParser::GraphContext::getRuleIndex() const {
  return DOTParser::RuleGraph;
}

void DOTParser::GraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraph(this);
}

void DOTParser::GraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraph(this);
}


antlrcpp::Any DOTParser::GraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitGraph(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::GraphContext* DOTParser::graph() {
  GraphContext *_localctx = _tracker.createInstance<GraphContext>(_ctx, getState());
  enterRule(_localctx, 0, DOTParser::RuleGraph);
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
    setState(29);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::STRICT) {
      setState(28);
      match(DOTParser::STRICT);
    }
    setState(31);
    _la = _input->LA(1);
    if (!(_la == DOTParser::GRAPH

    || _la == DOTParser::DIGRAPH)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(33);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DOTParser::NUMBER)
      | (1ULL << DOTParser::STRING)
      | (1ULL << DOTParser::ID)
      | (1ULL << DOTParser::HTML_STRING))) != 0)) {
      setState(32);
      id();
    }
    setState(35);
    match(DOTParser::T__0);
    setState(36);
    stmt_list();
    setState(37);
    match(DOTParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stmt_listContext ------------------------------------------------------------------

DOTParser::Stmt_listContext::Stmt_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DOTParser::StmtContext *> DOTParser::Stmt_listContext::stmt() {
  return getRuleContexts<DOTParser::StmtContext>();
}

DOTParser::StmtContext* DOTParser::Stmt_listContext::stmt(size_t i) {
  return getRuleContext<DOTParser::StmtContext>(i);
}


size_t DOTParser::Stmt_listContext::getRuleIndex() const {
  return DOTParser::RuleStmt_list;
}

void DOTParser::Stmt_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_list(this);
}

void DOTParser::Stmt_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_list(this);
}


antlrcpp::Any DOTParser::Stmt_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitStmt_list(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Stmt_listContext* DOTParser::stmt_list() {
  Stmt_listContext *_localctx = _tracker.createInstance<Stmt_listContext>(_ctx, getState());
  enterRule(_localctx, 2, DOTParser::RuleStmt_list);
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
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DOTParser::T__0)
      | (1ULL << DOTParser::GRAPH)
      | (1ULL << DOTParser::NODE)
      | (1ULL << DOTParser::EDGE)
      | (1ULL << DOTParser::SUBGRAPH)
      | (1ULL << DOTParser::NUMBER)
      | (1ULL << DOTParser::STRING)
      | (1ULL << DOTParser::ID)
      | (1ULL << DOTParser::HTML_STRING))) != 0)) {
      setState(39);
      stmt();
      setState(41);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DOTParser::T__2) {
        setState(40);
        match(DOTParser::T__2);
      }
      setState(47);
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

//----------------- StmtContext ------------------------------------------------------------------

DOTParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::Node_stmtContext* DOTParser::StmtContext::node_stmt() {
  return getRuleContext<DOTParser::Node_stmtContext>(0);
}

DOTParser::Edge_stmtContext* DOTParser::StmtContext::edge_stmt() {
  return getRuleContext<DOTParser::Edge_stmtContext>(0);
}

DOTParser::Attr_stmtContext* DOTParser::StmtContext::attr_stmt() {
  return getRuleContext<DOTParser::Attr_stmtContext>(0);
}

std::vector<DOTParser::IdContext *> DOTParser::StmtContext::id() {
  return getRuleContexts<DOTParser::IdContext>();
}

DOTParser::IdContext* DOTParser::StmtContext::id(size_t i) {
  return getRuleContext<DOTParser::IdContext>(i);
}

DOTParser::SubgraphContext* DOTParser::StmtContext::subgraph() {
  return getRuleContext<DOTParser::SubgraphContext>(0);
}


size_t DOTParser::StmtContext::getRuleIndex() const {
  return DOTParser::RuleStmt;
}

void DOTParser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void DOTParser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}


antlrcpp::Any DOTParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::StmtContext* DOTParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 4, DOTParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(56);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(48);
      node_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(49);
      edge_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(50);
      attr_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(51);
      id();
      setState(52);
      match(DOTParser::T__3);
      setState(53);
      id();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(55);
      subgraph();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_stmtContext ------------------------------------------------------------------

DOTParser::Attr_stmtContext::Attr_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::Attr_listContext* DOTParser::Attr_stmtContext::attr_list() {
  return getRuleContext<DOTParser::Attr_listContext>(0);
}

tree::TerminalNode* DOTParser::Attr_stmtContext::GRAPH() {
  return getToken(DOTParser::GRAPH, 0);
}

tree::TerminalNode* DOTParser::Attr_stmtContext::NODE() {
  return getToken(DOTParser::NODE, 0);
}

tree::TerminalNode* DOTParser::Attr_stmtContext::EDGE() {
  return getToken(DOTParser::EDGE, 0);
}


size_t DOTParser::Attr_stmtContext::getRuleIndex() const {
  return DOTParser::RuleAttr_stmt;
}

void DOTParser::Attr_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_stmt(this);
}

void DOTParser::Attr_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_stmt(this);
}


antlrcpp::Any DOTParser::Attr_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitAttr_stmt(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Attr_stmtContext* DOTParser::attr_stmt() {
  Attr_stmtContext *_localctx = _tracker.createInstance<Attr_stmtContext>(_ctx, getState());
  enterRule(_localctx, 6, DOTParser::RuleAttr_stmt);
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
    setState(58);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DOTParser::GRAPH)
      | (1ULL << DOTParser::NODE)
      | (1ULL << DOTParser::EDGE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(59);
    attr_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_listContext ------------------------------------------------------------------

DOTParser::Attr_listContext::Attr_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DOTParser::A_listContext *> DOTParser::Attr_listContext::a_list() {
  return getRuleContexts<DOTParser::A_listContext>();
}

DOTParser::A_listContext* DOTParser::Attr_listContext::a_list(size_t i) {
  return getRuleContext<DOTParser::A_listContext>(i);
}


size_t DOTParser::Attr_listContext::getRuleIndex() const {
  return DOTParser::RuleAttr_list;
}

void DOTParser::Attr_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_list(this);
}

void DOTParser::Attr_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_list(this);
}


antlrcpp::Any DOTParser::Attr_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitAttr_list(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Attr_listContext* DOTParser::attr_list() {
  Attr_listContext *_localctx = _tracker.createInstance<Attr_listContext>(_ctx, getState());
  enterRule(_localctx, 8, DOTParser::RuleAttr_list);
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
    setState(66); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(61);
      match(DOTParser::T__4);
      setState(63);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << DOTParser::NUMBER)
        | (1ULL << DOTParser::STRING)
        | (1ULL << DOTParser::ID)
        | (1ULL << DOTParser::HTML_STRING))) != 0)) {
        setState(62);
        a_list();
      }
      setState(65);
      match(DOTParser::T__5);
      setState(68); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == DOTParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- A_listContext ------------------------------------------------------------------

DOTParser::A_listContext::A_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DOTParser::IdContext *> DOTParser::A_listContext::id() {
  return getRuleContexts<DOTParser::IdContext>();
}

DOTParser::IdContext* DOTParser::A_listContext::id(size_t i) {
  return getRuleContext<DOTParser::IdContext>(i);
}


size_t DOTParser::A_listContext::getRuleIndex() const {
  return DOTParser::RuleA_list;
}

void DOTParser::A_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterA_list(this);
}

void DOTParser::A_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitA_list(this);
}


antlrcpp::Any DOTParser::A_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitA_list(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::A_listContext* DOTParser::a_list() {
  A_listContext *_localctx = _tracker.createInstance<A_listContext>(_ctx, getState());
  enterRule(_localctx, 10, DOTParser::RuleA_list);
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
    setState(78); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(70);
      id();
      setState(73);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DOTParser::T__3) {
        setState(71);
        match(DOTParser::T__3);
        setState(72);
        id();
      }
      setState(76);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DOTParser::T__6) {
        setState(75);
        match(DOTParser::T__6);
      }
      setState(80); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DOTParser::NUMBER)
      | (1ULL << DOTParser::STRING)
      | (1ULL << DOTParser::ID)
      | (1ULL << DOTParser::HTML_STRING))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edge_stmtContext ------------------------------------------------------------------

DOTParser::Edge_stmtContext::Edge_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::EdgeRHSContext* DOTParser::Edge_stmtContext::edgeRHS() {
  return getRuleContext<DOTParser::EdgeRHSContext>(0);
}

DOTParser::Node_idContext* DOTParser::Edge_stmtContext::node_id() {
  return getRuleContext<DOTParser::Node_idContext>(0);
}

DOTParser::SubgraphContext* DOTParser::Edge_stmtContext::subgraph() {
  return getRuleContext<DOTParser::SubgraphContext>(0);
}

DOTParser::Attr_listContext* DOTParser::Edge_stmtContext::attr_list() {
  return getRuleContext<DOTParser::Attr_listContext>(0);
}


size_t DOTParser::Edge_stmtContext::getRuleIndex() const {
  return DOTParser::RuleEdge_stmt;
}

void DOTParser::Edge_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdge_stmt(this);
}

void DOTParser::Edge_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdge_stmt(this);
}


antlrcpp::Any DOTParser::Edge_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitEdge_stmt(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Edge_stmtContext* DOTParser::edge_stmt() {
  Edge_stmtContext *_localctx = _tracker.createInstance<Edge_stmtContext>(_ctx, getState());
  enterRule(_localctx, 12, DOTParser::RuleEdge_stmt);
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
    setState(84);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DOTParser::NUMBER:
      case DOTParser::STRING:
      case DOTParser::ID:
      case DOTParser::HTML_STRING: {
        setState(82);
        node_id();
        break;
      }

      case DOTParser::T__0:
      case DOTParser::SUBGRAPH: {
        setState(83);
        subgraph();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(86);
    edgeRHS();
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::T__4) {
      setState(87);
      attr_list();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeRHSContext ------------------------------------------------------------------

DOTParser::EdgeRHSContext::EdgeRHSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DOTParser::EdgeopContext *> DOTParser::EdgeRHSContext::edgeop() {
  return getRuleContexts<DOTParser::EdgeopContext>();
}

DOTParser::EdgeopContext* DOTParser::EdgeRHSContext::edgeop(size_t i) {
  return getRuleContext<DOTParser::EdgeopContext>(i);
}

std::vector<DOTParser::Node_idContext *> DOTParser::EdgeRHSContext::node_id() {
  return getRuleContexts<DOTParser::Node_idContext>();
}

DOTParser::Node_idContext* DOTParser::EdgeRHSContext::node_id(size_t i) {
  return getRuleContext<DOTParser::Node_idContext>(i);
}

std::vector<DOTParser::SubgraphContext *> DOTParser::EdgeRHSContext::subgraph() {
  return getRuleContexts<DOTParser::SubgraphContext>();
}

DOTParser::SubgraphContext* DOTParser::EdgeRHSContext::subgraph(size_t i) {
  return getRuleContext<DOTParser::SubgraphContext>(i);
}


size_t DOTParser::EdgeRHSContext::getRuleIndex() const {
  return DOTParser::RuleEdgeRHS;
}

void DOTParser::EdgeRHSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeRHS(this);
}

void DOTParser::EdgeRHSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeRHS(this);
}


antlrcpp::Any DOTParser::EdgeRHSContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitEdgeRHS(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::EdgeRHSContext* DOTParser::edgeRHS() {
  EdgeRHSContext *_localctx = _tracker.createInstance<EdgeRHSContext>(_ctx, getState());
  enterRule(_localctx, 14, DOTParser::RuleEdgeRHS);
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
    setState(95); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(90);
      edgeop();
      setState(93);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case DOTParser::NUMBER:
        case DOTParser::STRING:
        case DOTParser::ID:
        case DOTParser::HTML_STRING: {
          setState(91);
          node_id();
          break;
        }

        case DOTParser::T__0:
        case DOTParser::SUBGRAPH: {
          setState(92);
          subgraph();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(97); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == DOTParser::T__7

    || _la == DOTParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeopContext ------------------------------------------------------------------

DOTParser::EdgeopContext::EdgeopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DOTParser::EdgeopContext::getRuleIndex() const {
  return DOTParser::RuleEdgeop;
}

void DOTParser::EdgeopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdgeop(this);
}

void DOTParser::EdgeopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdgeop(this);
}


antlrcpp::Any DOTParser::EdgeopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitEdgeop(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::EdgeopContext* DOTParser::edgeop() {
  EdgeopContext *_localctx = _tracker.createInstance<EdgeopContext>(_ctx, getState());
  enterRule(_localctx, 16, DOTParser::RuleEdgeop);
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
    setState(99);
    _la = _input->LA(1);
    if (!(_la == DOTParser::T__7

    || _la == DOTParser::T__8)) {
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

//----------------- Node_stmtContext ------------------------------------------------------------------

DOTParser::Node_stmtContext::Node_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::Node_idContext* DOTParser::Node_stmtContext::node_id() {
  return getRuleContext<DOTParser::Node_idContext>(0);
}

DOTParser::Attr_listContext* DOTParser::Node_stmtContext::attr_list() {
  return getRuleContext<DOTParser::Attr_listContext>(0);
}


size_t DOTParser::Node_stmtContext::getRuleIndex() const {
  return DOTParser::RuleNode_stmt;
}

void DOTParser::Node_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNode_stmt(this);
}

void DOTParser::Node_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNode_stmt(this);
}


antlrcpp::Any DOTParser::Node_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitNode_stmt(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Node_stmtContext* DOTParser::node_stmt() {
  Node_stmtContext *_localctx = _tracker.createInstance<Node_stmtContext>(_ctx, getState());
  enterRule(_localctx, 18, DOTParser::RuleNode_stmt);
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
    setState(101);
    node_id();
    setState(103);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::T__4) {
      setState(102);
      attr_list();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Node_idContext ------------------------------------------------------------------

DOTParser::Node_idContext::Node_idContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::IdContext* DOTParser::Node_idContext::id() {
  return getRuleContext<DOTParser::IdContext>(0);
}

DOTParser::PortContext* DOTParser::Node_idContext::port() {
  return getRuleContext<DOTParser::PortContext>(0);
}


size_t DOTParser::Node_idContext::getRuleIndex() const {
  return DOTParser::RuleNode_id;
}

void DOTParser::Node_idContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNode_id(this);
}

void DOTParser::Node_idContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNode_id(this);
}


antlrcpp::Any DOTParser::Node_idContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitNode_id(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::Node_idContext* DOTParser::node_id() {
  Node_idContext *_localctx = _tracker.createInstance<Node_idContext>(_ctx, getState());
  enterRule(_localctx, 20, DOTParser::RuleNode_id);
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
    setState(105);
    id();
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::T__9) {
      setState(106);
      port();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PortContext ------------------------------------------------------------------

DOTParser::PortContext::PortContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DOTParser::IdContext *> DOTParser::PortContext::id() {
  return getRuleContexts<DOTParser::IdContext>();
}

DOTParser::IdContext* DOTParser::PortContext::id(size_t i) {
  return getRuleContext<DOTParser::IdContext>(i);
}


size_t DOTParser::PortContext::getRuleIndex() const {
  return DOTParser::RulePort;
}

void DOTParser::PortContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPort(this);
}

void DOTParser::PortContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPort(this);
}


antlrcpp::Any DOTParser::PortContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitPort(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::PortContext* DOTParser::port() {
  PortContext *_localctx = _tracker.createInstance<PortContext>(_ctx, getState());
  enterRule(_localctx, 22, DOTParser::RulePort);
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
    setState(109);
    match(DOTParser::T__9);
    setState(110);
    id();
    setState(113);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::T__9) {
      setState(111);
      match(DOTParser::T__9);
      setState(112);
      id();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubgraphContext ------------------------------------------------------------------

DOTParser::SubgraphContext::SubgraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DOTParser::Stmt_listContext* DOTParser::SubgraphContext::stmt_list() {
  return getRuleContext<DOTParser::Stmt_listContext>(0);
}

tree::TerminalNode* DOTParser::SubgraphContext::SUBGRAPH() {
  return getToken(DOTParser::SUBGRAPH, 0);
}

DOTParser::IdContext* DOTParser::SubgraphContext::id() {
  return getRuleContext<DOTParser::IdContext>(0);
}


size_t DOTParser::SubgraphContext::getRuleIndex() const {
  return DOTParser::RuleSubgraph;
}

void DOTParser::SubgraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubgraph(this);
}

void DOTParser::SubgraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubgraph(this);
}


antlrcpp::Any DOTParser::SubgraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitSubgraph(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::SubgraphContext* DOTParser::subgraph() {
  SubgraphContext *_localctx = _tracker.createInstance<SubgraphContext>(_ctx, getState());
  enterRule(_localctx, 24, DOTParser::RuleSubgraph);
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
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DOTParser::SUBGRAPH) {
      setState(115);
      match(DOTParser::SUBGRAPH);
      setState(117);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << DOTParser::NUMBER)
        | (1ULL << DOTParser::STRING)
        | (1ULL << DOTParser::ID)
        | (1ULL << DOTParser::HTML_STRING))) != 0)) {
        setState(116);
        id();
      }
    }
    setState(121);
    match(DOTParser::T__0);
    setState(122);
    stmt_list();
    setState(123);
    match(DOTParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdContext ------------------------------------------------------------------

DOTParser::IdContext::IdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DOTParser::IdContext::ID() {
  return getToken(DOTParser::ID, 0);
}

tree::TerminalNode* DOTParser::IdContext::STRING() {
  return getToken(DOTParser::STRING, 0);
}

tree::TerminalNode* DOTParser::IdContext::HTML_STRING() {
  return getToken(DOTParser::HTML_STRING, 0);
}

tree::TerminalNode* DOTParser::IdContext::NUMBER() {
  return getToken(DOTParser::NUMBER, 0);
}


size_t DOTParser::IdContext::getRuleIndex() const {
  return DOTParser::RuleId;
}

void DOTParser::IdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterId(this);
}

void DOTParser::IdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DOTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitId(this);
}


antlrcpp::Any DOTParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DOTVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}

DOTParser::IdContext* DOTParser::id() {
  IdContext *_localctx = _tracker.createInstance<IdContext>(_ctx, getState());
  enterRule(_localctx, 26, DOTParser::RuleId);
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
    setState(125);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << DOTParser::NUMBER)
      | (1ULL << DOTParser::STRING)
      | (1ULL << DOTParser::ID)
      | (1ULL << DOTParser::HTML_STRING))) != 0))) {
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

// Static vars and initialization.
std::vector<dfa::DFA> DOTParser::_decisionToDFA;
atn::PredictionContextCache DOTParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DOTParser::_atn;
std::vector<uint16_t> DOTParser::_serializedATN;

std::vector<std::string> DOTParser::_ruleNames = {
  "graph", "stmt_list", "stmt", "attr_stmt", "attr_list", "a_list", "edge_stmt", 
  "edgeRHS", "edgeop", "node_stmt", "node_id", "port", "subgraph", "id"
};

std::vector<std::string> DOTParser::_literalNames = {
  "", "'{'", "'}'", "';'", "'='", "'['", "']'", "','", "'->'", "'--'", "':'"
};

std::vector<std::string> DOTParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "STRICT", "GRAPH", "DIGRAPH", 
  "NODE", "EDGE", "SUBGRAPH", "NUMBER", "STRING", "ID", "HTML_STRING", "COMMENT", 
  "LINE_COMMENT", "PREPROC", "WS"
};

dfa::Vocabulary DOTParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> DOTParser::_tokenNames;

DOTParser::Initializer::Initializer() {
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
       0x3, 0x1a, 0x82, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x3, 0x2, 0x5, 0x2, 0x20, 0xa, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x24, 0xa, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x2c, 0xa, 
       0x3, 0x7, 0x3, 0x2e, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x31, 0xb, 0x3, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x5, 0x4, 0x3b, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x42, 0xa, 0x6, 0x3, 0x6, 0x6, 
       0x6, 0x45, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x46, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x5, 0x7, 0x4c, 0xa, 0x7, 0x3, 0x7, 0x5, 0x7, 0x4f, 0xa, 
       0x7, 0x6, 0x7, 0x51, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x52, 0x3, 0x8, 
       0x3, 0x8, 0x5, 0x8, 0x57, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 
       0x5b, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x60, 0xa, 
       0x9, 0x6, 0x9, 0x62, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x63, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x6a, 0xa, 0xb, 0x3, 0xc, 
       0x3, 0xc, 0x5, 0xc, 0x6e, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0x74, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 
       0x78, 0xa, 0xe, 0x5, 0xe, 0x7a, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x2, 0x2, 0x10, 0x2, 
       0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
       0x1c, 0x2, 0x6, 0x3, 0x2, 0xe, 0xf, 0x4, 0x2, 0xe, 0xe, 0x10, 0x11, 
       0x3, 0x2, 0xa, 0xb, 0x3, 0x2, 0x13, 0x16, 0x2, 0x89, 0x2, 0x1f, 0x3, 
       0x2, 0x2, 0x2, 0x4, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x6, 0x3a, 0x3, 0x2, 
       0x2, 0x2, 0x8, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x44, 0x3, 0x2, 0x2, 
       0x2, 0xc, 0x50, 0x3, 0x2, 0x2, 0x2, 0xe, 0x56, 0x3, 0x2, 0x2, 0x2, 
       0x10, 0x61, 0x3, 0x2, 0x2, 0x2, 0x12, 0x65, 0x3, 0x2, 0x2, 0x2, 0x14, 
       0x67, 0x3, 0x2, 0x2, 0x2, 0x16, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x18, 0x6f, 
       0x3, 0x2, 0x2, 0x2, 0x1a, 0x79, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x7f, 0x3, 
       0x2, 0x2, 0x2, 0x1e, 0x20, 0x7, 0xd, 0x2, 0x2, 0x1f, 0x1e, 0x3, 0x2, 
       0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x3, 0x2, 0x2, 
       0x2, 0x21, 0x23, 0x9, 0x2, 0x2, 0x2, 0x22, 0x24, 0x5, 0x1c, 0xf, 
       0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 
       0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 0x3, 0x2, 0x2, 0x26, 
       0x27, 0x5, 0x4, 0x3, 0x2, 0x27, 0x28, 0x7, 0x4, 0x2, 0x2, 0x28, 0x3, 
       0x3, 0x2, 0x2, 0x2, 0x29, 0x2b, 0x5, 0x6, 0x4, 0x2, 0x2a, 0x2c, 0x7, 
       0x5, 0x2, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 
       0x2, 0x2, 0x2c, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x29, 0x3, 0x2, 0x2, 
       0x2, 0x2e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 
       0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 0x5, 0x3, 0x2, 0x2, 0x2, 0x31, 
       0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x3b, 0x5, 0x14, 0xb, 0x2, 0x33, 
       0x3b, 0x5, 0xe, 0x8, 0x2, 0x34, 0x3b, 0x5, 0x8, 0x5, 0x2, 0x35, 0x36, 
       0x5, 0x1c, 0xf, 0x2, 0x36, 0x37, 0x7, 0x6, 0x2, 0x2, 0x37, 0x38, 
       0x5, 0x1c, 0xf, 0x2, 0x38, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3b, 
       0x5, 0x1a, 0xe, 0x2, 0x3a, 0x32, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x33, 
       0x3, 0x2, 0x2, 0x2, 0x3a, 0x34, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x35, 0x3, 
       0x2, 0x2, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x7, 0x3, 0x2, 
       0x2, 0x2, 0x3c, 0x3d, 0x9, 0x3, 0x2, 0x2, 0x3d, 0x3e, 0x5, 0xa, 0x6, 
       0x2, 0x3e, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x41, 0x7, 0x7, 0x2, 0x2, 
       0x40, 0x42, 0x5, 0xc, 0x7, 0x2, 0x41, 0x40, 0x3, 0x2, 0x2, 0x2, 0x41, 
       0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x3, 0x2, 0x2, 0x2, 0x43, 0x45, 
       0x7, 0x8, 0x2, 0x2, 0x44, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 
       0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 
       0x2, 0x2, 0x47, 0xb, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4b, 0x5, 0x1c, 0xf, 
       0x2, 0x49, 0x4a, 0x7, 0x6, 0x2, 0x2, 0x4a, 0x4c, 0x5, 0x1c, 0xf, 
       0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 0x2, 0x2, 0x2, 
       0x4c, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4f, 0x7, 0x9, 0x2, 0x2, 0x4e, 
       0x4d, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x51, 
       0x3, 0x2, 0x2, 0x2, 0x50, 0x48, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 
       0x2, 0x2, 0x2, 0x52, 0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 
       0x2, 0x2, 0x53, 0xd, 0x3, 0x2, 0x2, 0x2, 0x54, 0x57, 0x5, 0x16, 0xc, 
       0x2, 0x55, 0x57, 0x5, 0x1a, 0xe, 0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 
       0x2, 0x56, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 
       0x58, 0x5a, 0x5, 0x10, 0x9, 0x2, 0x59, 0x5b, 0x5, 0xa, 0x6, 0x2, 
       0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 
       0xf, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x5, 0x12, 0xa, 0x2, 0x5d, 0x60, 
       0x5, 0x16, 0xc, 0x2, 0x5e, 0x60, 0x5, 0x1a, 0xe, 0x2, 0x5f, 0x5d, 
       0x3, 0x2, 0x2, 0x2, 0x5f, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x62, 0x3, 
       0x2, 0x2, 0x2, 0x61, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 0x2, 
       0x2, 0x2, 0x63, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 
       0x2, 0x64, 0x11, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x9, 0x4, 0x2, 0x2, 
       0x66, 0x13, 0x3, 0x2, 0x2, 0x2, 0x67, 0x69, 0x5, 0x16, 0xc, 0x2, 
       0x68, 0x6a, 0x5, 0xa, 0x6, 0x2, 0x69, 0x68, 0x3, 0x2, 0x2, 0x2, 0x69, 
       0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6d, 
       0x5, 0x1c, 0xf, 0x2, 0x6c, 0x6e, 0x5, 0x18, 0xd, 0x2, 0x6d, 0x6c, 
       0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x17, 0x3, 
       0x2, 0x2, 0x2, 0x6f, 0x70, 0x7, 0xc, 0x2, 0x2, 0x70, 0x73, 0x5, 0x1c, 
       0xf, 0x2, 0x71, 0x72, 0x7, 0xc, 0x2, 0x2, 0x72, 0x74, 0x5, 0x1c, 
       0xf, 0x2, 0x73, 0x71, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x3, 0x2, 0x2, 
       0x2, 0x74, 0x19, 0x3, 0x2, 0x2, 0x2, 0x75, 0x77, 0x7, 0x12, 0x2, 
       0x2, 0x76, 0x78, 0x5, 0x1c, 0xf, 0x2, 0x77, 0x76, 0x3, 0x2, 0x2, 
       0x2, 0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7a, 0x3, 0x2, 0x2, 0x2, 
       0x79, 0x75, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 
       0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x3, 0x2, 0x2, 0x7c, 0x7d, 
       0x5, 0x4, 0x3, 0x2, 0x7d, 0x7e, 0x7, 0x4, 0x2, 0x2, 0x7e, 0x1b, 0x3, 
       0x2, 0x2, 0x2, 0x7f, 0x80, 0x9, 0x5, 0x2, 0x2, 0x80, 0x1d, 0x3, 0x2, 
       0x2, 0x2, 0x15, 0x1f, 0x23, 0x2b, 0x2f, 0x3a, 0x41, 0x46, 0x4b, 0x4e, 
       0x52, 0x56, 0x5a, 0x5f, 0x63, 0x69, 0x6d, 0x73, 0x77, 0x79, 
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

DOTParser::Initializer DOTParser::_init;
