#include "pch.h"
#include "AdaptiveDebugSystem.h"

#include "State.h"
#include "StateMachine.h"
#include "StateTransition.h"
AdaptiveDebugSystem* AdaptiveDebugSystem::instance=nullptr;
struct Node
{
	Node(State* state) :
		f(0), g(0), h(0), state(state)
	{}
	int f, g, h;
	State* state;
};
bool cmp(const std::forward_list<Node> a, const std::forward_list<Node> b) {
	return a.begin()->f < b.begin()->f;
}

NCL::CSC8599::AdaptiveDebugSystem::AdaptiveDebugSystem() = default;

void AdaptiveDebugSystem::insert(Environment* env)
{
	env_container_.emplace_back(env);
}

void NCL::CSC8599::AdaptiveDebugSystem::update(float dt)
{
	const auto env = find_deadlock_env();
	if (env == nullptr)return;
	for(const auto i:env->second)
	{
		const auto path = re_plan(i);
		adjust(path,i);
	}
	EventSystem::getInstance()->PushEvent("fix_"+env->first,0);
}

void NCL::CSC8599::AdaptiveDebugSystem::adjust(Path path, StateMachine* state_machine)
{
	const auto size = path.size();
	for (size_t i = 0; i < size - 1; ++i)
	{
		const auto currentNode = path.top();
		path.pop();
		const auto destNode = path.top();
		auto currentNodeRange = state_machine->get_transitions(currentNode);
		auto destNodeRange = state_machine->get_transitions(destNode);
		for (auto& j = currentNodeRange.first; j != currentNodeRange.second; ++j)
		{
			if (j->second->GetDestinationState() == destNode)
			{
				j->second->CanTransition();
				break;
			}
		}
		//for (auto& k = destNodeRange.first; k != destNodeRange.second; ++k)
		//{
		//	if (k->second->GetDestinationState() == currentNode)
		//	{
		//		k->second->enable = false;// turn off previous trans
		//		break;
		//	}
		//}
	}
	state_machine->SetActiveComponent(path.top());
}

Environment* AdaptiveDebugSystem::find_deadlock_env()
{
	for (auto& env : env_container_)
	{
		for (const auto& state_machine : env->second)
		{//	TODO: stateMachine plus 
			const auto active = state_machine->get_active_component();
			const auto exp = state_machine->get_exp_component();
			if (exp == nullptr)   
				continue;
			if (active == exp)
				continue;
			auto range = state_machine->get_transitions(active);
			bool HasOutGoing = false;

			if(active)

			for (auto& i = range.first; i != range.second; ++i)
			{
				if (i->second->enable&& i->second->GetSourceState()!=i->second->GetDestinationState())
				{
					HasOutGoing = true;
					break;
				}
			}
			if (!HasOutGoing)
			{
				return env;
			}
		}
	}
	return nullptr;
}

NCL::CSC8599::Path NCL::CSC8599::AdaptiveDebugSystem::re_plan(StateMachine* state_machine)
{
	std::stack<State*> result;
	auto active= dynamic_cast<State*>(state_machine->get_active_component());
	auto exp= dynamic_cast<State*>(state_machine->get_exp_component());
	std::vector<std::forward_list<Node>> openList;
	std::vector<std::forward_list<Node>> closeList;

	auto allState = state_machine->get_component_container();
	auto allTrans = state_machine->get_all_transitions();
	auto node = Node(active);
	auto temp = std::forward_list<Node>();
	temp.push_front(node);
	openList.emplace_back(temp);

	while (!openList.empty())
	{
		std::sort(openList.begin(), openList.end(), cmp);
		auto currentNode = openList[0];
		openList.erase(openList.begin());
		closeList.emplace_back(currentNode);
		std::pair<TransitionIterator, TransitionIterator> range = allTrans.equal_range(currentNode.begin()->state);
		if (currentNode.begin()->state == exp)
		{
			for (auto i : currentNode)
			{
				result.push(i.state);
			}
			break;
		}
		auto currentG = currentNode.begin()->g;
		for (auto& i = range.first; i != range.second; ++i)
		{

			bool skip = false;
			const auto newState = dynamic_cast<State*>(i->second->GetDestinationState());
			auto newNode = Node(newState);
			for (auto j : closeList)
			{
				if (newNode.state == j.begin()->state)
				{
					skip = true;
					break;
				}
			}
			if (skip)continue;
			newNode.g = currentG + 1;
			newNode.h = -(newNode.state->expectation - exp->expectation);
			newNode.f = newNode.g + newNode.h;
			//newNode.f = newNode.g;

			std::forward_list<Node> currentNodeCopy(currentNode);
			currentNodeCopy.emplace_front(newNode);
			openList.emplace_back(currentNodeCopy);
		}
	}
	return result;
}
