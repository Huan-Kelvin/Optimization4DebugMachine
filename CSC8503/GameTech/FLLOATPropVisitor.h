
// Generated from antlr4/FLLOATProp.g by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "FLLOATPropParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by FLLOATPropParser.
 */
class  FLLOATPropVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by FLLOATPropParser.
   */
    virtual antlrcpp::Any visitNegation(FLLOATPropParser::NegationContext *context) = 0;

    virtual antlrcpp::Any visitParen(FLLOATPropParser::ParenContext *context) = 0;

    virtual antlrcpp::Any visitOr(FLLOATPropParser::OrContext *context) = 0;

    virtual antlrcpp::Any visitTop(FLLOATPropParser::TopContext *context) = 0;

    virtual antlrcpp::Any visitBot(FLLOATPropParser::BotContext *context) = 0;

    virtual antlrcpp::Any visitAnd(FLLOATPropParser::AndContext *context) = 0;

    virtual antlrcpp::Any visitAtom(FLLOATPropParser::AtomContext *context) = 0;


};

