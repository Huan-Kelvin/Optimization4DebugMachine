#include "pch.h"
#include "SharedStateMachine.h"
#include "StateTransition.h"
#include <stdexcept>

using namespace NCL::CSC8599;

void  SharedStateMachine::Update(float dt) {
	for (auto& it : activeComponents)
	{
		if (it.second == nullptr)return;
		it.second->Update(dt);
		//getInstance the transition set starting from this state node;
		auto range = get_transitions(it.second);

		for (auto& i = range.first; i != range.second; ++i)
		{
			if (!i->second->enable)continue;
			if (i->second->CanTransition())
			{
				std::cout << "Transitioning from " << GetStateName(it.second) << " to " << GetStateName(i->second->GetDestinationState()) << std::endl;
				it.second = i->second->GetDestinationState();
			}
		}
	}
}
std::string SharedStateMachine::Print(int index)
{
	for (auto& ac : activeComponents)
	{
		std::string active;
		for (auto& it : ComponentContainer)
		{
			if (it.second == ac.second)
			{
				active = it.first;
				break;
			}
		}
		std::string buffer("[StateMachine]");
		buffer += "<" + active + ">\n";
		for (auto i : ComponentContainer)
		{
			for (int j = 0; j < index; ++j) {
				buffer += "    ";
			}
			buffer += "(" + i.first + ")" + i.second->Print(index + 1);
		}
		return buffer;
	}
}

void SharedStateMachine::AddTransition(StateTransition* t) {
	allTransitions.insert(std::make_pair(t->GetSourceState(), t));
}

void SharedStateMachine::GetActiveComponentArr(std::vector<std::string>& arr)
{
	throw std::runtime_error("SharedStateMachine::GetActiveComponentArr(std::vector<std::string>& arr) is not supported.");
}

void SharedStateMachine::GetActiveComponentArr(AbstractStateMachine* machine,std::vector<std::string>& arr)
{
	for (auto& it : ComponentContainer)
	{
		if (it.second == activeComponents[machine])
		{
			arr.emplace_back(it.first);
		}
		it.second->GetActiveComponentArr(arr);
	}
}

std::pair<TransitionIterator, TransitionIterator> SharedStateMachine::get_transitions(AbstractComponent* state)
{
	return allTransitions.equal_range(state);
}
