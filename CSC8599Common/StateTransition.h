#pragma once
#include "AbstractComponent.h"
#include "EventSystem.h"
#include "../CSC8503/GameTech/easy_prop.h"
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		class State;
		using StateTransitionFunction = std::function<bool()>;
		class StateTransition {
		public:
			StateTransition(AbstractComponent* source, AbstractComponent* dest, StateTransitionFunction f, std::string _trigger,
				bool _enable=true) {
				sourceState = source;
				destinationState = dest;
				transitionFunction = std::move(f);
				//trigger = _trigger;
				trigger_ep = easy_prop(_trigger);
				enable = _enable;
			}
			StateTransition(AbstractComponent* source, AbstractComponent* dest, StateTransitionFunction f, easy_prop _trigger,
				bool _enable=true) {
				sourceState = source;
				destinationState = dest;
				transitionFunction = std::move(f);
				trigger_ep = _trigger;
				enable = _enable;
			}
			bool CanTransition() const;
			AbstractComponent* GetDestinationState() const { return destinationState; }
			AbstractComponent* GetSourceState() const { return sourceState; }
			bool enable;

			//const std::string& GetTrigger() const { return trigger; }
			const easy_prop& GetTriggerEP() const { return trigger_ep; }

		protected:
			AbstractComponent* sourceState;
			AbstractComponent* destinationState;
			StateTransitionFunction transitionFunction;
			//std::string trigger;
			
			easy_prop trigger_ep;

		};
	}
}
