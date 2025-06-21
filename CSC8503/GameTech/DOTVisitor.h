
// Generated from src/knobab/flloat_deps/DOT.g by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "DOTParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DOTParser.
 */
class  DOTVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DOTParser.
   */
    virtual antlrcpp::Any visitGraph(DOTParser::GraphContext *context) = 0;

    virtual antlrcpp::Any visitStmt_list(DOTParser::Stmt_listContext *context) = 0;

    virtual antlrcpp::Any visitStmt(DOTParser::StmtContext *context) = 0;

    virtual antlrcpp::Any visitAttr_stmt(DOTParser::Attr_stmtContext *context) = 0;

    virtual antlrcpp::Any visitAttr_list(DOTParser::Attr_listContext *context) = 0;

    virtual antlrcpp::Any visitA_list(DOTParser::A_listContext *context) = 0;

    virtual antlrcpp::Any visitEdge_stmt(DOTParser::Edge_stmtContext *context) = 0;

    virtual antlrcpp::Any visitEdgeRHS(DOTParser::EdgeRHSContext *context) = 0;

    virtual antlrcpp::Any visitEdgeop(DOTParser::EdgeopContext *context) = 0;

    virtual antlrcpp::Any visitNode_stmt(DOTParser::Node_stmtContext *context) = 0;

    virtual antlrcpp::Any visitNode_id(DOTParser::Node_idContext *context) = 0;

    virtual antlrcpp::Any visitPort(DOTParser::PortContext *context) = 0;

    virtual antlrcpp::Any visitSubgraph(DOTParser::SubgraphContext *context) = 0;

    virtual antlrcpp::Any visitId(DOTParser::IdContext *context) = 0;


};

