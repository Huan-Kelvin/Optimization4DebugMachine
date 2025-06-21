//
// Created by giacomo on 12/07/22.
//

#include "ltlf.h"


ltlf::ltlf() : casusu{TRUE}, is_negated{false} { }

ltlf::ltlf(const std::string &act) : casusu{ACT}, act{act}, is_negated{false} {}

ltlf::ltlf(formula_t citki) : casusu{citki}, is_negated{false}   {}

struct ltlf ltlf::True() { return {}; }

struct ltlf ltlf::Act(const std::string &act, bool negated) { ltlf toRet {act}; toRet.is_negated = negated; return toRet; }

struct ltlf ltlf::Neg(const ltlf &sub) {
    ltlf formula{NEG_OF};
    formula.args.emplace_back(sub);
    return formula;
}

struct ltlf ltlf::Next(const ltlf &sub) {
    ltlf formula{NEXT};
    formula.args.emplace_back(sub);
    return formula;
}

struct ltlf ltlf::Or(const ltlf &left, const ltlf &right) {
    struct ltlf formula{OR};
    formula.args.emplace_back(left);
    formula.args.emplace_back(right);
    return formula;
}

struct ltlf ltlf::And(const ltlf &left, const ltlf &right) {
    struct ltlf formula{AND};
    formula.args.emplace_back(left);
    formula.args.emplace_back(right);
    return formula;
}

struct ltlf ltlf::Diamond(const ltlf &sub, bool isForGraphs) {
    if (isForGraphs) return Until(ltlf::True(), sub);
    ltlf formula{DIAMOND};
    formula.args.emplace_back(sub);
    return formula;
}

struct ltlf ltlf::Box(const ltlf &sub, bool isForGraphs) {
    if (isForGraphs) return  Release({FALSE}, sub);
    ltlf formula{BOX};
    formula.args.emplace_back(sub);
    return formula;
}

struct ltlf ltlf::Last() {
    return Neg(Next(True()));
}

struct ltlf ltlf::Until(const ltlf &left, const ltlf &right) {
    struct ltlf formula{UNTIL};
    formula.args.emplace_back(left);
    formula.args.emplace_back(right);
    return formula;
}

struct ltlf ltlf::Release(const ltlf &left, const ltlf &right) {
    struct ltlf formula{RELEASE};
    formula.args.emplace_back(left);
    formula.args.emplace_back(right);
    return formula;
}

struct ltlf ltlf::Implies(const ltlf &left, const ltlf &right, bool isGraphGeneration) {
    if (isGraphGeneration) {
        return Or(Neg(left), right);
    } else {
        auto res = Or(Neg(left), And(left, right));
        return res;
    }
}

struct ltlf ltlf::Equivalent(const ltlf &left, const ltlf &right, bool isForGraphs) {
    return And(Implies(left, right, isForGraphs), Implies(right, left, isForGraphs));
}

struct ltlf ltlf::WeakUntil(const ltlf &left, const ltlf &right, bool isForGraphs) {
    return Or(Until(left, right), Box(left, isForGraphs));
}


std::ostream &operator<<(std::ostream &os, const ltlf &syntax) {
    std::string reset = "";
    if (syntax.is_negated)
        os << "!";
    switch (syntax.casusu) {
        case ACT:
            return os << syntax.act << reset;
        case NEG_OF:
            return os << "(!(" << syntax.args[0] << "))"<< reset;
        case OR:
            return os << "(" << syntax.args[0] << ") | (" << syntax.args[1] << ')'<< reset;
        case AND:
            return os << "(" << syntax.args[0] << ") & (" << syntax.args[1] << ')'<< reset;
        case NEXT:
            return os << "X(" << syntax.args[0] << ")"<< reset;
        case UNTIL:
            return os << "(" << syntax.args[0] << ") U (" << syntax.args[1] << ')'<< reset;
        case RELEASE:
            return os << "(" << syntax.args[0] << ") R (" << syntax.args[1] << ')'<< reset;
        case TRUE:
            return os << "true"<< reset;
        case BOX:
            return os << "G(" << syntax.args[0] << ")"<< reset;
        case DIAMOND:
            return os << "F(" << syntax.args[0] << ")"<< reset;
        default:
            return os << "false"<< reset;
    }
}


bool ltlf::easy_interpret(const std::string &map) const {
    switch (casusu) {
        case TRUE:
            return true;
        case FALSE:
            return false;
        case ACT:
            if (!is_negated) {
                bool res = (map == (act));
                return res;
            } else {
                bool res = !(map == (act));
                return res;
            }
        case NEG_OF:
            return !args.at(0).easy_interpret(map);
        case OR: {
            return args.at(0).easy_interpret(map) || args.at(1).easy_interpret( map);
        }
        case AND: {
            return args.at(0).easy_interpret(map) && args.at(1).easy_interpret( map);
        }
        case NEXT:
            return args.at(0).easy_interpret(map); // Stops the interpretation before the current element
        default:
            assert(false);
    }
}
