#include "pch.h"
#include "SharedStateMachine.h"
#include "StateTransition.h"
#include <stdexcept>

using namespace NCL::CSC8599;

void  SharedStateMachine::Update(float dt) {
	for (auto& it : activeComponentsSM)
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
	for (auto& it : activeComponentsObj)
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
	std::string buffer("[SharedStateMachine]\n");

	for (const auto& machinePair : activeComponentsSM)
	{
		std::string activeName;
		for (const auto& comp : ComponentContainer)
		{
			if (comp.second == machinePair.second)
			{
				activeName = comp.first;
				break;
			}
		}

		for (int j = 0; j < index; ++j) {
			buffer += "    ";
		}
		buffer += "StateMachine@" + std::to_string(reinterpret_cast<std::uintptr_t>(machinePair.first));
		buffer += " <" + activeName + ">\n";

		for (const auto& comp : ComponentContainer)
		{
			for (int j = 0; j < index + 1; ++j) {
				buffer += "    ";
			}
			buffer += "(" + comp.first + ")" + comp.second->Print(index + 2);
		}
	}

	for (const auto& machinePair : activeComponentsObj)
	{
		std::string activeName;
		for (const auto& comp : ComponentContainer)
		{
			if (comp.second == machinePair.second)
			{
				activeName = comp.first;
				break;
			}
		}

		for (int j = 0; j < index; ++j) {
			buffer += "    ";
		}
		buffer += "StateMachine@" + std::to_string(reinterpret_cast<std::uintptr_t>(machinePair.first));
		buffer += " <" + activeName + ">\n";

		for (const auto& comp : ComponentContainer)
		{
			for (int j = 0; j < index + 1; ++j) {
				buffer += "    ";
			}
			buffer += "(" + comp.first + ")" + comp.second->Print(index + 2);
		}
	}

	return buffer;
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
		if (it.second == activeComponentsSM[machine])
		{
			arr.emplace_back(it.first);
		}
		it.second->GetActiveComponentArr(arr);
	}
}
void SharedStateMachine::GetActiveComponentArr(GameObject* object,std::vector<std::string>& arr)
{
	for (auto& it : ComponentContainer)
	{
		if (it.second == activeComponentsObj[object])
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
