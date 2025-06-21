#include "pch.h"
#include "StateMachinePlus.h"

void NCL::CSC8599::StateMachinePlus::Update(float dt)
{
	for (const auto& i : ComponentContainer)
	{
		auto subStateMachine = i.second;
		if (subStateMachine)
			subStateMachine->Update(dt);
	}
}

std::string NCL::CSC8599::StateMachinePlus::Print(int index)
{
	std::string buffer("[StateMachinePlus]\n");
	for (auto i : ComponentContainer)
	{
		for (int j = 0; j < index; ++j) {
			buffer += "    ";
		}
		buffer += "(" + i.first + ")" + i.second->Print(index + 1);
	}
	return buffer;
}

void StateMachinePlus::GetActiveComponentArr(std::vector<std::string>& arr)
{
	for (auto& it : ComponentContainer)
	{
		it.second->GetActiveComponentArr(arr);
	}
}
