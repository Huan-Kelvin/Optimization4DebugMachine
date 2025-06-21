
// Generated from antlr4/FLLOATProp.g by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "FLLOATPropVisitor.h"


/**
 * This class provides an empty implementation of FLLOATPropVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  FLLOATPropBaseVisitor : public FLLOATPropVisitor {
public:

  virtual antlrcpp::Any visitNegation(FLLOATPropParser::NegationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParen(FLLOATPropParser::ParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOr(FLLOATPropParser::OrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTop(FLLOATPropParser::TopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBot(FLLOATPropParser::BotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnd(FLLOATPropParser::AndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAtom(FLLOATPropParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }


};

