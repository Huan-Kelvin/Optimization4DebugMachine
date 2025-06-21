
// Generated from src/knobab/flloat_deps/DOT.g by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "DOTVisitor.h"


/**
 * This class provides an empty implementation of DOTVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DOTBaseVisitor : public DOTVisitor {
public:

  virtual antlrcpp::Any visitGraph(DOTParser::GraphContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmt_list(DOTParser::Stmt_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmt(DOTParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttr_stmt(DOTParser::Attr_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttr_list(DOTParser::Attr_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitA_list(DOTParser::A_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdge_stmt(DOTParser::Edge_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeRHS(DOTParser::EdgeRHSContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeop(DOTParser::EdgeopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNode_stmt(DOTParser::Node_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNode_id(DOTParser::Node_idContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPort(DOTParser::PortContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubgraph(DOTParser::SubgraphContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitId(DOTParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }


};

