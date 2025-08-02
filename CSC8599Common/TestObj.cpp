#pragma once
#include "pch.h"
#include "TestObj.h"
#include "EventSystem.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"
#include "State.h"
#include "StateTransition.h"
#include "TypeObject.h"

using namespace NCL;
using namespace CSC8503;
using namespace CSC8599;

TestObj::TestObj(string name) :GameObject(name) {
	init_state_machine();
	GameWorld::Get()->AddGameObject(this);
}

void TestObj::update(float dt) {
	if(state_machine) state_machine->Update(dt);
	
	TestObjType::Instance().showHUD(transform, std::to_string(static_cast<int>(health)));

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::M))
	{
		//new TestObj("testObj2");
		auto name = TestObjType::Instance().GetStateMachine()->GetCurStateName(this);
		std::cout << "name : " << name << std::endl;
	}
}
SharedStateMachine* TestObj::get_shared_state_machine() const {
	return TestObjType::Instance().GetStateMachine();
}

void TestObj::init_state_machine()
{
	TestObjType::Instance().GetStateMachine()->AddStatemachine(this);

	return;
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
	state_machine = new StateMachine("init", init, end);
	state_machine->AddComponent("stateA", stateA);
	state_machine->AddComponent("stateB", stateB);
	state_machine->AddComponent("stateC", stateC);
	state_machine->AddComponent("end", end);

	//state_machine->AddTransition(new CSC8599::StateTransition(init, stateA, [this]()->bool
	//	{
	//		return true;
	//	}, "test0"));
	lastState = init;
	t1 = new CSC8599::StateTransition(init, stateA, [this]()->bool
		{
			return true;
		}, "");
	state_machine->AddTransition(t1);

	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateB, [this, stateA]()->bool
		{
			lastState = stateA;
			return true;
		}, "test1"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateA, [this, stateB]()->bool
		{
			lastState = stateB;
			return true;
		}, "test2"));

	state_machine->AddTransition(new CSC8599::StateTransition(stateB, stateC, [this, stateB]()->bool
		{
			lastState = stateB;
			return true;
		}, "test3"));
	state_machine->AddTransition(new CSC8599::StateTransition(stateA, stateC, [this, stateA]()->bool
		{
			std::cout << "Check health of testObj : " 
				<< dynamic_cast<CSC8599::TestObj*>(GameWorld::Get()->find_game_object("testObj"))->GetHealth() << std::endl;
			lastState = stateA;
			return true;
		}, "test3"));

	t2 = new CSC8599::StateTransition(stateC, init, [this, init]()->bool
		{
			lastState = init;
			return true;
		}, "test0");

	state_machine->AddTransition(t2);
}

void TestObj::ReturnToLastState() {
	if (lastState) {
		state_machine->SetActiveComponent(state_machine->GetComponent(state_machine->GetStateName(lastState)));
		std::cout << "Return to state : " << state_machine->GetStateName(lastState)
			<< "	# Can state C quit : " << (t2->enable ? "true" : "false") << std::endl << std::endl;
	}
	else {
		std::cout << "No last state to return to." << std::endl;
	}
}

void TestObj::BlockTransition() {
	std::cout << "BlockTransition" << std::endl;
	state_machine->BlockTransition();
}

void TestObj::TakeDamage(float damage)
{
	TestObjType::Instance().takeDamage(*this, damage);
}