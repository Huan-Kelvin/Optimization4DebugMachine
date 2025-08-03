#pragma once
#include "flloat_wrapper.h"
#include "ltlf.h"
#include <unordered_map>	
#include "../../CSC8599Common/StateMachine.h"
#include "../../CSC8599Common/SharedStateMachine.h"
namespace NCL {
	namespace CSC8599 {
		class StateMachineParser
		{
		public:
			StateMachine* parse(ltlf& formula, std::unordered_set<std::string>& sigmaAll);
			StateMachine* parse2(ltlf& formula);
			SharedStateMachine* parseTest(ltlf& formula);
			static StateMachineParser* getInstance();

			void Clear() { ltlfStateMachines.clear(); }
		private:
			static StateMachineParser* uniqueInstance;
			StateMachineParser();
			// Python wrapper, to be instantiated only once in the program! (it should be a singleton!)
			FLLOAT callable; // python callable

			std::unordered_map<ltlf, SharedStateMachine*> ltlfStateMachines;
		};
	}
}