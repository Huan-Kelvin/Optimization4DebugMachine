#pragma once
#include <stack>

#include "State.h"
#include "StateMachinePlus.h"

namespace NCL
{
	namespace CSC8503
	{
		class State;
	}
}

namespace NCL {
	namespace CSC8599
	{
		class DebugStateMachine :public StateMachinePlus
		{
		public:
			DebugStateMachine();
			~DebugStateMachine() override;
		};
	}
}


