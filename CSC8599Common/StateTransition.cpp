#pragma once
#include "pch.h"
#include "StateTransition.h"
bool NCL::CSC8599::StateTransition::CanTransition() const
{
	//auto event = EventSystem::getInstance()->HasHappened(trigger);
	auto event_ep = EventSystem::getInstance()->HasHappened(trigger_ep);

	//if (trigger.empty()|| event) {
	//	return transitionFunction();
	//}

	if (trigger_ep.empty() || !event_ep.empty()) {
		return transitionFunction();
	}

	return false;
}
