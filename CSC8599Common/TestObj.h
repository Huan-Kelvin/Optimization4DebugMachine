#pragma once
#include "../CSC8503/CSC8503Common/GameObject.h"
#include "StateMachine.h"
#include "State.h"
namespace NCL {
	namespace CSC8599
	{
		class TestObj :public CSC8503::GameObject
		{
		public:
			TestObj(string name = "");
			void update(float dt) override;

			StateMachine* get_state_machine()const { return state_machine; }

			void ReturnToLastState();

			float GetHealth() const { return health; }

		private:
			StateMachine* state_machine = nullptr;
			void init_state_machine();

			float health = 100.0f;

			CSC8599::StateTransition* t1;
			CSC8599::StateTransition* t2;
			CSC8599::StateTransition* t3;

			CSC8599::State* lastState;
		};
	}
}
