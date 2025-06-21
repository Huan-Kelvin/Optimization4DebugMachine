#pragma once
#include <vector>
#include <map>

namespace NCL {
	namespace CSC8503 {

		class State;
		class StateTransition;

		typedef std::multimap<State*, StateTransition*> TransitionContainer;//使用空间和模板导致了很笨拙的变量名 用typedef 节省了空间和时间
		typedef TransitionContainer::iterator TransitionIterator;

		class StateMachine	{
		public:
			StateMachine();//保证activestate从一个安全的空指针开始
			~StateMachine();//销毁的时候要删除所有的状态和转变

			void AddState(State* s);
			void AddTransition(StateTransition* t);//使用multimap表示状态机的有向图性质 源状态作为Map的键 转换本身作为值

			void Update(float dt);

		protected:
			State * activeState;

			std::vector<State*> allStates;

			TransitionContainer allTransitions;
		};
	}
}