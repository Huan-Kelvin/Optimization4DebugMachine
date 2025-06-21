//
// Created by giacomo on 12/07/22.
//

#ifndef GRAPHS_LTLF_H
#define GRAPHS_LTLF_H


/*
 * ltlf.h
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
// Created by giacomo on 18/02/21.
//



#include <unordered_set>

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

enum formula_t {
    ACT,
    NEG_OF,
    OR,
    AND,
    NEXT,
    UNTIL,
    RELEASE,
    TRUE,
    FALSE,
    NUMERIC_ATOM,
    BOX,
    DIAMOND,
    LAST
};



#include <string>
#include <vector>
#include <ostream>
#include <cassert>


struct ltlf {
    formula_t              casusu;
    std::string            act;
    std::vector<std::string> rewritten_act;
    std::vector<ltlf>      args;
    bool                   is_negated;

    // C++ constructors
    ltlf();
    ltlf(const std::string& act);
    ltlf(formula_t citki);
    ltlf(const ltlf&) = default;
    ltlf(ltlf&&) = default;
    ltlf& operator=(const ltlf&) = default;
    ltlf& operator=(ltlf&&) = default;


    // Semantic constructors
    static struct ltlf True();

    static struct ltlf False() {
        ltlf f{};
        f.is_negated = true;
        return f;
    };
    static struct ltlf Act(const std::string& act, bool isNegated = false);
    static struct ltlf Neg(const ltlf& sub);
    static struct ltlf Next(const ltlf& sub);
    static struct ltlf Or(const ltlf& left, const ltlf& right);
    static struct ltlf And(const ltlf& left, const ltlf& right);
    static struct ltlf Until(const ltlf& left, const ltlf& right);
    static struct ltlf Release(const ltlf& left, const ltlf& right);
    static struct ltlf Diamond(const ltlf& sub, bool isGraphGeneration = true);
    static struct ltlf Box(const ltlf& sub, bool isGraphGeneration = true);
    static struct ltlf Last();
    static struct ltlf Implies(const ltlf& left, const ltlf& right, bool isGraphGeneration = true);
    static struct ltlf Equivalent(const ltlf& left, const ltlf& right, bool isGraphGeneration = true);
    static struct ltlf WeakUntil(const ltlf& left, const ltlf& right, bool isForGraphs = true);

    bool easy_interpret(const std::string& map) const;


private:
    //struct ltlf _interpret2(const std::unordered_set<struct ltlf>& map) const;
    // void _allActions(std::unordered_set<std::string> &labels) const;
};

std::ostream &operator<<(std::ostream &os, const ltlf &syntax);

#endif //GRAPHS_LTLF_H
