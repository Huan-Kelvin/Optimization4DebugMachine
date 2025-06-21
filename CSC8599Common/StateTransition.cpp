#include "pch.h"
#include "StateTransition.h"
bool NCL::CSC8599::StateTransition::CanTransition() const
{
	auto event = EventSystem::getInstance()->HasHappened(trigger);
	if (trigger.empty() || event) return transitionFunction(event);
	return false;
}
