#pragma once
#include "flloat_wrapper.h"
#include "ltlf.h"
#include "../../CSC8599Common/StateMachine.h"
class StateMachineParser
{
public:
	NCL::CSC8599::StateMachine* parse(ltlf& formula, std::unordered_set<std::string>& sigmaAll);
	static StateMachineParser* getInstance();
private:
	static StateMachineParser* uniqueInstance;
	StateMachineParser();
	// Python wrapper, to be instantiated only once in the program! (it should be a singleton!)
	FLLOAT callable; // python callable
};

