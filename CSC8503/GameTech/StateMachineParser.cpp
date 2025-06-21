#include "StateMachineParser.h"
#include "../../CSC8599Common/State.h"
#include "easy_prop.h"
#include "FlexibleFA.h"
#include "set_operations.h"

#include "ParseFFLOATDot.h"
#include "../../CSC8599Common/StateTransition.h"
using namespace NCL::CSC8599;
StateMachineParser* StateMachineParser::uniqueInstance = nullptr;

inline
std::unordered_set<std::string> evaluate_easy_prop_to_atoms(const easy_prop& prop,
    const std::unordered_set<std::string>& sigma) {
    switch (prop.casusu) {
    case easy_prop::E_P_AND:
        //            DEBUG_ASSERT(prop.args.size() == 2);
        //            DEBUG_ASSERT(!prop.isAtomNegated);
        return unordered_intersection(evaluate_easy_prop_to_atoms(prop.args.at(0)/*, bogus_act_to_atom*/, sigma),
            evaluate_easy_prop_to_atoms(prop.args.at(1)/*, bogus_act_to_atom*/, sigma));
    case easy_prop::E_P_OR: {
        //            DEBUG_ASSERT(prop.args.size() == 2);
        //            DEBUG_ASSERT(!prop.isAtomNegated);
        auto S = evaluate_easy_prop_to_atoms(prop.args.at(0)/*, bogus_act_to_atom*/, sigma);
        auto tmp = evaluate_easy_prop_to_atoms(prop.args.at(1)/*, bogus_act_to_atom*/, sigma);
        S.insert(tmp.begin(), tmp.end());
        return S;
    }
    case easy_prop::E_P_ATOM:
        //            DEBUG_ASSERT(prop.args.empty());
        //            DEBUG_ASSERT(bogus_act_to_set.contains(prop.single_atom_if_any));
        if (prop.isAtomNegated) {
            auto it = sigma.find(prop.single_atom_if_any);
            if (it != sigma.end()) {
                return unordered_difference(sigma, { prop.single_atom_if_any });
            }
            else {
                return sigma;
            }
        }
        else {
            return { prop.single_atom_if_any };
        }
    case easy_prop::E_P_TRUE:
        return sigma;
    default: //case easy_prop::E_P_FALSE:
        return {};
    }
}
NCL::CSC8599::StateMachine* StateMachineParser::parse(ltlf& formula, std::unordered_set<std::string>& sigmaAll)
{
    std::stringstream s;
    // Representing the formula as per online syntax
    s << formula;

    // Graph in the dotviz representation
    std::string dot_graph = callable(s.str());
    // Representing the string as a stream
    std::stringstream file{ dot_graph };

    // Parsing the file by reading the graphviz representation for it
    ParseFFLOATDot graph_loader;
    auto patternGraphToInstantiate = graph_loader.parse(file);

    // Converting the graph with propositions into a DFA
    FlexibleFA<size_t, std::string> result;
    std::unordered_map<size_t, size_t> idConv;
    for (size_t nodeId = 0, N = patternGraphToInstantiate.maximumNodeId(); nodeId < N; nodeId++) {
        size_t src = result.addNewNodeWithLabel(nodeId);
        idConv[nodeId] = src;
    }
    for (size_t finalNodes : patternGraphToInstantiate.fini()) {
        result.addToFinalNodesFromId(idConv.at(finalNodes));
    }
    for (size_t initialNodes : patternGraphToInstantiate.init()) {
        result.addToInitialNodesFromId(idConv.at(initialNodes));
    }
    for (size_t nodeId = 0, N = patternGraphToInstantiate.maximumNodeId(); nodeId < N; nodeId++) {
        size_t src = idConv.at(nodeId);
        for (const auto& edge : patternGraphToInstantiate.outgoingEdges(nodeId)) {
            // std::cerr << edge.first << std::endl;
            size_t dst = idConv.at(edge.second);
            for (const std::string& act : evaluate_easy_prop_to_atoms(edge.first/*, bogus_act_to_atom*/, sigmaAll)) {
                result.addNewEdgeFromId(src, dst, act);
            }
        }
    }
    result.makeDFAAsInTheory(sigmaAll);

    // Printing the result into the terminal in a graphviz syntax
    result.dot(std::cout);
    std::cout << std::endl;

    auto allNodes = result.getNodeIds();
    auto allEdges = result.getEdgeIds();

    std::map<size_t,State*> parsedNodes;
    std::vector<StateTransition*> parsedEdges;

    for(auto i:allNodes)
    {
        auto state = new State(nullptr);
        parsedNodes.insert(std::make_pair(i,state));
    }
    for(auto i:allNodes)
    {
        auto outGoing = result.outgoingEdges(i);
        auto inGoing = result.ingoingEdges(i);
        for (auto j : outGoing)
        {
            auto startNode = parsedNodes.find(i);
            auto destNode = parsedNodes.find(j.second);
            auto temp = std::string();
            if (j.first == "other"&& startNode!=destNode)temp = "";
            else temp = j.first;
            auto trans = new StateTransition(startNode->second, destNode->second, 
                [](EVENT*)->bool
                {
	                return true;
                }, temp);

            parsedEdges.emplace_back(trans);
            bool skip = false;
           for(auto k:inGoing)
           {
               if (k.second == j.second)
                   skip = true;
           }
           if(!skip)
           {
               auto trans = new StateTransition(destNode->second, startNode->second,
                   [](EVENT*)->bool
                   {
	                   return true;
                   }, j.first,false);
               parsedEdges.emplace_back(trans);
           }
        }
    }
	auto state_machine = new StateMachine(std::to_string(allNodes[0]),
        parsedNodes.find(allNodes[0])->second, parsedNodes.find(allNodes[0])->second);

    for (int i = 1; i < allNodes.size(); ++i)
    {
        state_machine->AddComponent(std::to_string(allNodes[i]),parsedNodes.find(allNodes[i])->second);
    }
    for(auto i:parsedEdges)
    {
        state_machine->AddTransition(i);
    }

    return state_machine;//state_machine;
}

StateMachineParser* StateMachineParser::getInstance()
{

    if (uniqueInstance == nullptr) {
        uniqueInstance = new StateMachineParser();
    }
    return uniqueInstance;
}

StateMachineParser::StateMachineParser()
{

}
