#pragma once
#include "AbstractStateMachine.h"
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		class StateMachinePlus : public AbstractStateMachine {
		public:
			StateMachinePlus() = default;
			~StateMachinePlus() override = default;
			void Update(float dt) override;
			std::string Print(int index) override;
			void GetActiveComponentArr(std::vector<std::string>& arr) override;
		};
	}
}
