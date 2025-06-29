//
// Created by giacomo on 12/07/22.
//

#ifndef GRAPHS_EASY_PROP_H
#define GRAPHS_EASY_PROP_H


#include <iostream>

#include <string>
#include <set>
#include <vector>
#include <functional>

struct easy_prop {
    enum t {
        E_P_AND,
        E_P_OR,
        E_P_ATOM,
        E_P_TRUE,
        E_P_FALSE
    };
    t casusu;
    bool isAtomNegated;
    std::vector<easy_prop> args;
    std::string single_atom_if_any;

    easy_prop(t casusu);
    easy_prop();
    easy_prop(const std::string& s) :casusu{ E_P_ATOM }, isAtomNegated{ false }, single_atom_if_any{ s } {};

    easy_prop(const easy_prop&) = default;
    easy_prop(easy_prop&&) = default;
    easy_prop& operator=(const easy_prop&) = default;
    easy_prop& operator=(easy_prop&&) = default;

    friend bool operator==(const easy_prop& lhs, const easy_prop& rhs) {
        return lhs.casusu == rhs.casusu &&
            lhs.isAtomNegated == rhs.isAtomNegated &&
            lhs.args == rhs.args &&
            lhs.single_atom_if_any == rhs.single_atom_if_any;
    }

    bool empty() const {
        return casusu == E_P_ATOM && single_atom_if_any.empty();
	}

    bool evaluate(const std::set<std::string>& s) const {
        switch (casusu) {
        case E_P_ATOM: {
            bool contains = s.find(single_atom_if_any) != s.end();
            return isAtomNegated ? !contains : contains;
        }
        case E_P_TRUE:
            return true;
        case E_P_FALSE:
            return false;
        case E_P_AND:
            for (const auto& sub : args) {
                if (!sub.evaluate(s)) return false;
            }
            return true;
        case E_P_OR:
            for (const auto& sub : args) {
                if (sub.evaluate(s)) return true;
            }
            return false;
        }
    }
    static easy_prop And(const easy_prop& a, const easy_prop& b) {
        easy_prop result;
        result.casusu = E_P_AND;
        result.args = { a, b };
		result.isAtomNegated = false;
        return result;
    }
    static easy_prop Or(const easy_prop& a, const easy_prop& b) {
        easy_prop result;
        result.casusu = E_P_OR;
        result.args = { a, b };
        result.isAtomNegated = false;
        return result;
    }
    static easy_prop Not(const easy_prop& a) {
        easy_prop result = a;
        result.isAtomNegated = !a.isAtomNegated;
        return result;
    }


    static void collectAtoms(const easy_prop& prop, std::set<std::string>& result) {
        switch (prop.casusu) {
        case E_P_ATOM:
            if (!prop.single_atom_if_any.empty()) {
                result.insert(prop.single_atom_if_any);
            }
            break;
        case E_P_AND:
        case E_P_OR:
            for (const auto& sub : prop.args) {
                collectAtoms(sub, result);
            }
            break;
        default:
            break;
        }
    }
    static std::set<std::string> getAtoms(const easy_prop& prop) {
        std::set<std::string> atoms;
        collectAtoms(prop, atoms);
        return atoms;
    }

};

#endif //GRAPHS_EASY_PROP_H
