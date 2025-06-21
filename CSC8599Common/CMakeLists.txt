cmake_minimum_required(VERSION 3.22)
project(graphs)

find_package(Boost 1.74 COMPONENTS python)
find_package(PythonLibs)
set(CMAKE_CXX_STANDARD 20)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(submodules/antlr4/runtime/Cpp)
include_directories(submodules/antlr4/runtime/Cpp/runtime/src)
include_directories(submodules/antlr4/submodules/json/include)

add_executable(graphs main.cpp flloat_wrapper.h flloat_wrapper.cpp easy_prop.cpp easy_prop.h ltlf.cpp ltlf.h ParseFFLOATDot.cpp ParseFFLOATDot.h
        DOTBaseListener.cpp
        DOTBaseVisitor.cpp
        DOTLexer.cpp
        DOTListener.cpp
        DOTParser.cpp
        DOTVisitor.cpp
        ParseFFLOATDot.cpp
        FLLOATPropBaseListener.cpp
        FLLOATPropBaseVisitor.cpp
        FLLOATPropLexer.cpp
        FLLOATPropListener.cpp
        FLLOATPropParser.cpp
        FLLOATPropVisitor.cpp
        evaluateHashes.c
        hash_combine.cpp
        hashing.cpp
        FLLOATSimplePropParser.cpp NodeLabelBijectionFA.h NodeLabelBijectionGraph.h adjacency_graph.cpp adjacency_graph.h FlexibleFA.h FlexibleGraph.h set_operations.h)
target_link_libraries(graphs ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} antlr4_shared)