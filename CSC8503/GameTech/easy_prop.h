//
// Created by giacomo on 12/07/22.
//

#ifndef GRAPHS_EASY_PROP_H
#define GRAPHS_EASY_PROP_H


#include <iostream>



#include <string>
#include <vector>

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
    easy_prop(const easy_prop&) = default;
    easy_prop(easy_prop&&) = default;
    easy_prop& operator=(const easy_prop&) = default;
    easy_prop& operator=(easy_prop&&) = default;
};

#endif //GRAPHS_EASY_PROP_H
