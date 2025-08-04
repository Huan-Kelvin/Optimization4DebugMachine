#pragma once
#include "EventSystem.h"
#include "TypeObject.h"
#include "State.h"
#include "StateTransition.h"
#include "../Common/Window.h"
#include "ExtendCharacter.h"
using namespace NCL;
using namespace NCL::CSC8503;
using namespace NCL::CSC8599;

std::vector<TypeObject*> TypeObject::instances;

void CharacterType::takeDamage(ExtendCharacter* obj, float amount, GameObject* source)
{
	if (obj->GetCurHealth() > 0) obj->HealthChange(-amount);
}

void TestObjType::InitStateMachine()
{
	if (state_machine) return;
	auto init = new State([this](float dt)->void
		{
			//std::cout << "In state init" << std::endl;
			//if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
			//{
			//	t1->enable = !t1->enable;
			//}
		});
	auto stateA = new State([this](float dt)->void
		{
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
			{
				t2->enable = !t2->enable;
			}
		});
	auto stateB = new State([this](float dt)->void
		{
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
			{
				t2->enable = !t2->enable;
			}
		});
	auto stateC = new State([this](float dt)->void
		{
			//std::cout << "In state C" << std::endl;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
			{
				t2->enable = !t2->enable;
			}
		});
	auto end = new State([this](float dt)->void
		{
			//std::cout << "In state end" << std::endl;
		});
	state_machine = new SharedStateMachine("init", init, end);
	state_machine->AddComponent("stateA", stateA);
	state_machine->AddComponent("stateB", stateB);
	state_machine->AddComponent("stateC", stateC);
	state_machine->AddComponent("end", end);

	//state_machine->AddTransition(new CSC8599::StateTransition(init, stateA, [this]()->bool
	//	{
	//		return true;
	//	}, "test0"));
	t1 = new CSC8599::StateTransition(init, stateA, [this]()->bool
		{
			//std::cout << "Transitioning from init to stateA" << std::endl;
			return true;
		},"");
	state_machine->AddTransition(t1);

	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateB, [this, stateA]()->bool
		{
			//lastState = stateA;
			return true;
		}, "test1"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateA, [this, stateB]()->bool
		{
			//lastState = stateB;
			return true;
		}, "test2"));

	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateC, [this, stateB]()->bool
		{
			//lastState = stateB;
			return true;
		}, "test3"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateC, [this, stateA]()->bool
		{
			//std::cout << "Check health of testObj : "
			//	<< dynamic_cast<CSC8599::TestObj*>(GameWorld::Get()->find_game_object("testObj"))->GetHealth() << std::endl;
			//lastState = stateA;

			//auto event = EventSystem::getInstance()->HasHappened("test3");
			//for (auto& it : event->vArg)
			//{
			//	std::cout << "Check name "<< it << std::endl;
			//	if (it == state_machine->GetCurUpdateObject()->GetName()) {
			//		return true;
			//	}
			//}
			//return false;

			return true;
		}, "test3"));

	t2 = new CSC8599::StateTransition(stateC, init, [this, init]()->bool
		{
			//lastState = init;
			return true;
		}, "test0");

	state_machine->AddTransition(t2);
}

void NCL::CSC8599::DeviceType::BlockTrans(ExtendCharacter* cha)
{
	state_machine->BlockObject((GameObject*)cha);
	if (cha->sourseObj->GetName()=="enemy")
	{
		state_machine->SetActiveComponent(cha, state_machine->GetComponent("Hostile"));
		cha->ResetHealth();
	}
	else if (cha->sourseObj->GetName() == "player") {
		state_machine->SetActiveComponent(cha, state_machine->GetComponent("Friendly"));
		cha->ResetHealth();
	}
}

void DeviceType::takeDamage(ExtendCharacter* obj, float amount, GameObject* source)
{
	if (state_machine->GetCurStateName(obj) == "Destroyed") return;
	if (source->GetName() == "player" && state_machine->GetCurStateName(obj) == "Friendly")	return;
	if (source->GetName() == "enemy" && state_machine->GetCurStateName(obj) == "Hostile")	return;

	if (obj->GetCurHealth() > 0) obj->HealthChange(-amount);

	if (obj->GetCurHealth() <= 0) {
		if (source->GetName() == "player")
			EventSystem::getInstance()->PushEvent("test1", 1, obj->GetName());
		else if (source->GetName() == "enemy")
			EventSystem::getInstance()->PushEvent("test2", 1, obj->GetName());
	}
}

void DeviceType::InitStateMachine()
{
	auto init = new State([this](float dt)->void
		{

		});
	auto stateA = new State([this](float dt)->void
		{

		});
	auto stateB = new State([this](float dt)->void
		{

		});
	auto end = new State([this](float dt)->void
		{
		});
	state_machine = new SharedStateMachine("Neutral", init, end);
	state_machine->AddComponent("Friendly", stateA);
	state_machine->AddComponent("Hostile", stateB);
	state_machine->AddComponent("Destroyed", end);

	state_machine->AddTransition(new CSC8599::StateTransition(init, stateA, [this]()->bool
		{
			auto obj = dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject());
			if (obj->GetCurHealth() > 0) return false;
			obj->ResetHealth();
			return true;
		}, "test1"));
	state_machine->AddTransition(new CSC8599::StateTransition(init, stateB, [this]()->bool
		{
			auto obj = dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject());
			if (obj->GetCurHealth() > 0) return false;
			obj->ResetHealth();
			return true;
		}, "test2"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateB, [this]()->bool
		{
			auto obj = dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject());
			if (obj->GetCurHealth() > 0) return false;
			obj->ResetHealth();
			return true;
		}, "test2"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateA, [this]()->bool
		{
			auto obj = dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject());
			if (obj->GetCurHealth() > 0) return false;
			obj->ResetHealth();
			return true;
		}, "test1"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateA, end, [this]()->bool
		{
			auto& name = state_machine->GetCurUpdateObject()->GetName();
			auto event = EventSystem::getInstance()->HasHappened("test3");
			if (event && event->vArg.size() == 1 && event->vArg[0] == name)
			{
				std::cout << "\n\t" << name << " is being destroyed!" << std::endl;
				return true;
			}
			return false;
		}, "test3"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateB, end, [this]()->bool
		{
			auto& name = state_machine->GetCurUpdateObject()->GetName();
			auto event = EventSystem::getInstance()->HasHappened("test3");
			if (event && event->vArg.size() == 1 && event->vArg[0] == name)
			{
				std::cout << "\n\t" << name << " is being destroyed!" << std::endl;
				return true;
			}
			return false;
		}, "test3"));
	state_machine->AddTransition(new CSC8599::StateTransition(end, init, [this]()->bool
		{
			auto obj = dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject());
			if (obj->GetCurHealth() > 0) return false;
			obj->ResetHealth();
			return true;
		}, "test0"));
}

void PlayerType::InitStateMachine()
{
	auto init = new State([this](float dt)->void
		{

		});
	auto stateA = new State([this](float dt)->void
		{

		});
	auto end = new State([this](float dt)->void
		{

		});

	state_machine = new SharedStateMachine("init", init, end);
	state_machine->AddComponent("idle", stateA);
	state_machine->AddComponent("dead", end);

	state_machine->AddTransition(new CSC8599::StateTransition(init, stateA, [this]()->bool
		{
			return true;
		}, ""));
	state_machine->AddTransition(new CSC8599::StateTransition(stateA, end, [this]()->bool
		{
			return dynamic_cast<ExtendCharacter*>(state_machine->GetCurUpdateObject())->GetCurHealth() <= 0;
		}, ""));
}
