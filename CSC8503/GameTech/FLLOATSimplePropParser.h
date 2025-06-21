/*
 * FLLOATSimplePropParser.h
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

#ifndef BPM21_FLLOATSIMPLEPROPPARSER_H
#define BPM21_FLLOATSIMPLEPROPPARSER_H

namespace antlr4 {
    class ANTLRInputStream;
    class CommonTokenStream;
}
class FLLOATPropLexer;
class FLLOATPropParser;
#include "FLLOATPropBaseVisitor.h"
#include <sstream>
//#include <utils/strings.h>
//#include <magic_enum.hpp>
#include <fstream>
#include "ltlf.h"
#include "easy_prop.h"

/**
 * Propositions parses from the FLLOAT output, using a specific sympy format
 */
class FLLOATSimplePropParser : public FLLOATPropVisitor {

public:
    FLLOATSimplePropParser(){}
    ~FLLOATSimplePropParser() {}

    easy_prop parse(std::istream& stream);

    antlrcpp::Any visitNegation(FLLOATPropParser::NegationContext *context) override;
    antlrcpp::Any visitAtom(FLLOATPropParser::AtomContext *context) override;
    antlrcpp::Any visitParen(FLLOATPropParser::ParenContext *context) override;
    antlrcpp::Any visitOr(FLLOATPropParser::OrContext *context) override;
    antlrcpp::Any visitTop(FLLOATPropParser::TopContext *context) override;
    antlrcpp::Any visitBot(FLLOATPropParser::BotContext *context) override;
    antlrcpp::Any visitAnd(FLLOATPropParser::AndContext *context) override;
};


#endif //BPM21_FLLOATSIMPLEPROPPARSER_H
