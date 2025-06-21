//
// Created by giacomo on 14/11/2021.
//

//#define PYTHON_WORKS

#ifndef KNOBAB_FLLOAT_WRAPPER_H
#define KNOBAB_FLLOAT_WRAPPER_H

#include <boost/python.hpp>
#include <string>
class FLLOAT {
    boost::python::object flloat_parser_ltlf, flloat_ltlf;
public:
    FLLOAT();
    std::string operator()(const std::string& ltlf);
};

#endif //KNOBAB_FLLOAT_WRAPPER_H
