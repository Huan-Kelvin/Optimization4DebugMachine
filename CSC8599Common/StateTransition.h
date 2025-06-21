#pragma once
#include "AbstractComponent.h"
#include "EventSystem.h"
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		class State;
		using StateTransitionFunction = std::function<bool(EVENT*)>;
		class StateTransition {
		public:
			StateTransition(AbstractComponent* source, AbstractComponent* dest, StateTransitionFunction f, std::string _trigger,
				bool _enable=true) {
				sourceState = source;
				destinationState = dest;
				transitionFunction = std::move(f);
				trigger = _trigger;
				enable = _enable;
			}
			bool CanTransition() const;
			AbstractComponent* GetDestinationState() const { return destinationState; }
			AbstractComponent* GetSourceState() const { return sourceState; }
			bool enable;
		protected:
			AbstractComponent* sourceState;
			AbstractComponent* destinationState;
			StateTransitionFunction transitionFunction;
			std::string trigger;
		};
	}
}
