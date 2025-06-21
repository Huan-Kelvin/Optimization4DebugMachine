#include "pch.h"
#include "DebugStateMachine.h"

#include "State.h"
#include "StateTransition.h"
#include "StateMachine.h"


NCL::CSC8599::DebugStateMachine::DebugStateMachine()
{
	//auto A = new StateMachine("0",
	//	new State([this](float dt)->void
	//	{
	//		time_stack = 0.0f;
	//	}));
	//A->AddComponent("1", new State([this](float dt)->void
	//	{
	//		time_stack += dt;
	//		if (time_stack > 1.5f)
	//			EventSystem::getInstance()->PushEvent("Debug_PetTaunt", 0);
	//	}));
	//A->AddTransition(new CSC8599::StateTransition(A->GetComponent("0"), A->GetComponent("1"), [this](EVENT* event)->bool
	//{
	//		return EventSystem::getInstance()->HasHappened("player_over_threat");
	//	/*&&
	//			(EventSystem::getInstance()->HasHappened("player_die")||
	//				!EventSystem::getInstance()->HasHappened("Debug_PetTaunt"))
	//			use LTL_TO_EDGES 
	//	*/
	//},""));
	//A->AddTransition(new CSC8599::StateTransition(A->GetComponent("1"), A->GetComponent("0"), [this](EVENT* event)->bool
	//{
	//		return EventSystem::getInstance()->HasHappened("Debug_PetTaunt");
	//	/*&&
	//			!EventSystem::getInstance()->HasHappened("player_die")

	//	*/
	//}, ""));


	//auto B = new StateMachine("2",
	//	new State([this](float dt)->void
	//	{}));

	//B->AddComponent("1", new State([this](float dt)->void
	//{
	//}));
	//B->AddComponent("0", new State([this](float dt)->void
	//	{
	//		EventSystem::getInstance()->PushEvent("Debug_PetDie", 0);
	//	}));

	//B->AddTransition(new CSC8599::StateTransition(B->GetComponent("2"), B->GetComponent("1"), [this](EVENT* event)->bool
	//	{
	//	return EventSystem::getInstance()->HasHappened("player_die");
	//	}, ""));
	//B->AddTransition(new CSC8599::StateTransition(B->GetComponent("1"), B->GetComponent("2"), [this](EVENT* event)->bool
	//	{
	//		return true;
	//	}, "pet_die"));

	//B->AddTransition(new CSC8599::StateTransition(B->GetComponent("1"), B->GetComponent("0"), [this](EVENT* event)->bool
	//	{
	//	return !EventSystem::getInstance()->HasHappened("pet_die");
	//	}, ""));
	//B->AddTransition(new CSC8599::StateTransition(B->GetComponent("0"), B->GetComponent("2"), [this](EVENT* event)->bool
	//	{
	//		return true;
	//	}, "pet_die"));

	//auto state0 = new  State([this](float dt)->void
	//	{

	//	});
	//auto state1=new  State([this](float dt)->void
	//{
	//	
	//});

	//auto state2 = new  State([this](float dt)->void
	//	{

	//	});
	//auto state3 = new  State([this](float dt)->void
	//	{

	//	});

	//state1->expectation = 0;
	//state2->expectation = 1;
	//state3->expectation = 2;
	//state0->expectation = 3;

}

NCL::CSC8599::DebugStateMachine::~DebugStateMachine()
= default;

