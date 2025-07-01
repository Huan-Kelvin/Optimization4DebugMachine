#pragma once
#include "StateMachine.h"
namespace NCL {
	namespace CSC8599
	{
		class TestObj
		{
		public:
			TestObj();
			void Update(float dt);

			StateMachine* get_state_machine()const { return state_machine; }

		private:
			StateMachine* state_machine = nullptr;
			void init_state_machine();

			CSC8599::StateTransition* t1;
			CSC8599::StateTransition* t2;
			CSC8599::StateTransition* t3;
		};
	}
}
