/*
 * ParseFFLOATDot.h
 * This file is part of bpm21
 *
 * Copyright (C) 2021 - Giacomo Bergami
 *
 * bpm21 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * bpm21 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bpm21. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 13/03/21.
//

#ifndef BPM21_PARSEFFLOATDOT_H
#define BPM21_PARSEFFLOATDOT_H

namespace antlr4 {
    class ANTLRInputStream;
    class CommonTokenStream;
}
class DADLexer;
class DADParser;
#include "DOTBaseVisitor.h"
#include <sstream>
//#include <yaucl/utils/strings.h>
//#include <magic_enum.hpp>
#include <fstream>
#include "NodeLabelBijectionFA.h"
//#include <yaucl/graphs/FlexibleFA.h>
#include "ltlf.h"
#include "easy_prop.h"

class ParseFFLOATDot : public DOTVisitor {

    NodeLabelBijectionFA<std::string, easy_prop> parsing_result;
public:

    ///bool need_back_conversion;
    ///const std::unordered_map<std::string, std::string>* back_conv;

    ParseFFLOATDot() /*: back_conv{nullptr}, need_back_conversion{false}*/ {}
    ~ParseFFLOATDot()  {}

    NodeLabelBijectionFA<std::string, easy_prop> parse(std::istream &stream);
    antlrcpp::Any visitGraph(DOTParser::GraphContext *context) override;
    antlrcpp::Any visitStmt_list(DOTParser::Stmt_listContext *context) override;
    antlrcpp::Any visitStmt(DOTParser::StmtContext *context) override;
    antlrcpp::Any visitAttr_stmt(DOTParser::Attr_stmtContext *context) override;
    antlrcpp::Any visitAttr_list(DOTParser::Attr_listContext *context) override;
    antlrcpp::Any visitA_list(DOTParser::A_listContext *context) override;
    antlrcpp::Any visitEdge_stmt(DOTParser::Edge_stmtContext *context) override;
    antlrcpp::Any visitEdgeRHS(DOTParser::EdgeRHSContext *context) override;
    antlrcpp::Any visitEdgeop(DOTParser::EdgeopContext *context) override;
    antlrcpp::Any visitNode_stmt(DOTParser::Node_stmtContext *context) override;
    antlrcpp::Any visitNode_id(DOTParser::Node_idContext *context) override;
    antlrcpp::Any visitPort(DOTParser::PortContext *context) override;
    antlrcpp::Any visitSubgraph(DOTParser::SubgraphContext *context) override;
    antlrcpp::Any visitId(DOTParser::IdContext *context) override;
};


/*FlexibleFA<size_t, std::string> getFAFromLTLFEdges(const std::unordered_set<std::string> &SigmaAll,
                                                   const NodeLabelBijectionFA<std::string, ltlf> &parsing_result2) ;*/

#endif //BPM21_PARSEFFLOATDOT_H
