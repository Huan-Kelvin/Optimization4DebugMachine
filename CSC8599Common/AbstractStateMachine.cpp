#include "pch.h"
#include "AbstractStateMachine.h"
#include "State.h"
void NCL::CSC8599::AbstractStateMachine::AddComponent(const std::string& name, AbstractComponent* compoent)
{
	ComponentContainer.insert(std::make_pair(name, compoent));
}

NCL::CSC8599::AbstractComponent* NCL::CSC8599::AbstractStateMachine::GetComponent(const std::string& name)
{
	auto temp = ComponentContainer.find(name);
	if (temp != ComponentContainer.end())return temp->second;
	for (const auto& i : ComponentContainer) {
		if (dynamic_cast<State*>(i.second) == nullptr) {
			auto sub = (AbstractStateMachine*)(i.second);
			AbstractComponent* result = sub->GetComponent(name);
			if (result != nullptr)return result;
		}
	}
	return nullptr;
}

std::string NCL::CSC8599::AbstractStateMachine::GetStateName(AbstractComponent* comp)
{
	for (const auto& pair : ComponentContainer)
	{
		if (pair.second == comp)
			return pair.first;
		if (auto sub = dynamic_cast<AbstractStateMachine*>(pair.second))
		{
			std::string result = sub->GetStateName(comp);
			if (!result.empty())
				return result;
		}
	}
	return "";
}
