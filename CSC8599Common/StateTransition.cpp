#include "pch.h"
#include "StateTransition.h"
bool NCL::CSC8599::StateTransition::CanTransition() const
{
	auto event = EventSystem::getInstance()->HasHappened(trigger);
	auto event_ep = EventSystem::getInstance()->HasHappened(trigger_ep);
	// HasHappened(trigger_ep)
	// And other conditions like isHealthPositive
	if ((trigger.empty() && trigger_ep.args.empty())
		|| event || event_ep) return transitionFunction(event);
	return false;
}