#include "pch.h"
#include "StateMachine.h"
#include "StateTransition.h"
void  NCL::CSC8599::StateMachine::Update(float dt) {
	if (activeComponent == nullptr)return;
	activeComponent->Update(dt);
	//getInstance the transition set starting from this state node;
	auto range = get_transitions(activeComponent);

	for (auto& i = range.first; i != range.second; ++i)
	{
		if (!i->second->enable)continue;
		if (i->second->CanTransition())
		{
			activeComponent = i->second->GetDestinationState();
		}
	}
}
std::string NCL::CSC8599::StateMachine::Print(int index)
{
	std::string active;
	for (auto& it : ComponentContainer)
	{
		if (it.second == activeComponent)
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
void NCL::CSC8599::StateMachine::AddTransition(StateTransition* t) {
	allTransitions.insert(std::make_pair(t->GetSourceState(), t));
}

void StateMachine::GetActiveComponentArr(std::vector<std::string>& arr)
{
	for (auto& it : ComponentContainer)
	{
		if (it.second == activeComponent)
		{
			arr.emplace_back(it.first);
		}
		it.second->GetActiveComponentArr(arr);
	}
}

std::pair<TransitionIterator, TransitionIterator> StateMachine::get_transitions(AbstractComponent* state)
{
	 return allTransitions.equal_range(state);
}
