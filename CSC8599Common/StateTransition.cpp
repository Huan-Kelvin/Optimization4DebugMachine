#include "pch.h"
#include "StateTransition.h"
bool NCL::CSC8599::StateTransition::CanTransition() const
{
	auto event = EventSystem::getInstance()->HasHappened(trigger);
	auto event_ep = EventSystem::getInstance()->HasHappened(trigger_ep);

	if ((trigger.empty() && trigger_ep.empty())
		|| event || event_ep) return transitionFunction();

	return false;
}
