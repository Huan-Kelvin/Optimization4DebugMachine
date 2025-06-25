#include "pch.h"
#include "TestObj.h"
#include "EventSystem.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"
#include "State.h"
#include "StateTransition.h"

using namespace NCL;
using namespace CSC8503;
using namespace CSC8599;

TestObj::TestObj()
{
	init_state_machine();

	//EventSystem::getInstance()->RegisterEventHandler("test0", [this](EVENT* p_event)->void
	//	{
	//	});
}

void TestObj::Update(float dt) {
	state_machine->Update(dt);
}

void TestObj::init_state_machine()
{
	auto init = new State([this](float dt)->void
		{			
			//std::cout << "Enter state init" << std::endl;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM0))
			{
				EventSystem::getInstance()->PushEvent("test0", 0);
			}
		});
	auto stateA = new State([this](float dt)->void
		{
			std::cout << "Enter state A" << std::endl;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM1))
			{
				std::cout << "Transitioning to state B from A" << std::endl;
				EventSystem::getInstance()->PushEvent("test1", 0);
			}
		});
	auto stateB = new State([this](float dt)->void
		{
			std::cout << "Enter state B" << std::endl;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM2))
			{
				EventSystem::getInstance()->PushEvent("test2", 0);
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM4))
			{
				EventSystem::getInstance()->PushEvent("test4", 0);
			}
		});
	auto stateC = new State([this](float dt)->void
		{
			std::cout << "Enter state C" << std::endl;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM3))
			{
				EventSystem::getInstance()->PushEvent("test3", 0);
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
			{
				t2->enable = false;
				t3->enable = false;
			}
		});
	auto end = new State([this](float dt)->void
		{
			std::cout << "Enter state end" << std::endl;
		});
	state_machine = new StateMachine("A", init, end);
	state_machine->AddComponent("stateA", stateA);
	state_machine->AddComponent("stateB", stateB);
	state_machine->AddComponent("stateC", stateC);
	state_machine->AddComponent("end", end);

	state_machine->AddTransition(new CSC8599::StateTransition(init, stateA, [this](EVENT* event)->bool
		{
			return true;
		}, "test0"));

	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateB, [this](EVENT* event)->bool
		{
			return true;
		}, "test1"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateA, [this](EVENT* event)->bool
		{
			return true;
		}, "test4"));
	t2 = new CSC8599::StateTransition(stateB, stateC, [this](EVENT* event)->bool
		{
			return true;
		}, "test2");
	state_machine->AddTransition(t2);
	t3 = new CSC8599::StateTransition(stateC, stateA, [this](EVENT* event)->bool
		{
			return true;
		}, "test3");
	state_machine->AddTransition(t3);
}