#include "pch.h"
#include "Pet.h"

#include "EventSystem.h"
#include "State.h"
#include "PetController.h"
#include "../CSC8503/CSC8503Common/Debug.h"
#include "Monster.h"
#include <thread>

#include "../CSC8503/CSC8503Common/GameWorld.h"
static  std::string models[3] = {"passive","assist","protect"};
void tesk()
{}
Pet::Pet(Character* _owner) :owner(_owner)
{
	init_attrs("pet.json");
	user_controller_ = new PetController();
	EventSystem::getInstance()->RegisterEventHandler("on_hit", [this](EVENT* p_event)->void
		{
			if (!isAlive())return;
			const int source = stoi(p_event->vArg[0]);
			const int id = stoi(p_event->vArg[1]);
			if (id == owner->GetWorldID())
			{
				switch_target(source);
				if (model == ControlModelType::PROTECT)
				{
					const auto stateMachine = get_state_machine();
					const auto actions = dynamic_cast<StateMachine*>(stateMachine->GetComponent("actions"));
					const auto attack = stateMachine->GetComponent("attack");
					actions->SetActiveComponent(attack);
				}
			}

		});
	EventSystem::getInstance()->RegisterEventHandler("fix_DebugA", [this](EVENT* p_event)->void
		{
			const auto _target = dynamic_cast<Monster*>(target);
			if (_target)  
			{
				_target->get_taunt(GetWorldID());
				EventSystem::getInstance()->PushEvent("pet_taunt", 0);
			}
		});
	EventSystem::getInstance()->RegisterEventHandler("fix_DebugB", [this](EVENT* p_event)->void
		{
			data temp;
			temp._int = 0;
			set_attr("health", temp);
		});
}


void Pet::update(float dt)
{
	Character::update(dt);
	target = owner->get_target();
}

void Pet::UI_update(const Matrix4& viewMatrix, const Matrix4 projectMatrix)
{
	Character::UI_update(viewMatrix, projectMatrix);
	showHUD(viewMatrix,projectMatrix, models[static_cast<int>(model)], 9.f);
}


bool Pet::attack_to_prepare()
{
	std::vector<std::string> arr;
	owner->get_state_machine()->GetActiveComponentArr(arr);
	auto _target = dynamic_cast<Character*> (target);
	if (model == ControlModelType::PASSIVE)return !_target->isAlive()||user_controller_->get_inputs().buttons[STOP];
	if (model == ControlModelType::ASSIST)return std::find(arr.begin(), arr.end(), "prepare") != arr.end();
	if (model == ControlModelType::PROTECT)return !_target->isAlive()||user_controller_->get_inputs().buttons[STOP];
	return false;
}

bool Pet::prepare_to_attack()
{
	if (target == nullptr)return false;
	const auto _target = dynamic_cast<Character*>(target);
	if (!_target)return false;
	const auto health = _target->get_attr("health")._int;
	const auto input = user_controller_->get_inputs();

	std::vector<std::string> arr;
	owner->get_state_machine()->GetActiveComponentArr(arr);

	if (model == ControlModelType::PASSIVE)return health > 0 && input.buttons[ATTACK];
	if (model == ControlModelType::ASSIST)return std::find(arr.begin(), arr.end(), "attack") != arr.end();
	if (model == ControlModelType::PROTECT)return false;
	return false;
}

bool Pet::alive_to_dead()
{
	const auto result = Character::alive_to_dead();
	if(result)EventSystem::getInstance()->PushEvent("pet_die", 1, std::to_string(GetWorldID()).c_str());
	return result;
}

bool Pet::move_to_stand()
{
	std::vector<std::string> arr;
	owner->get_state_machine()->GetActiveComponentArr(arr);
	return std::find(arr.begin(), arr.end(), "stand") != arr.end();
}

bool Pet::stand_to_move()
{
	std::vector<std::string> arr;
	owner->get_state_machine()->GetActiveComponentArr(arr);
	return std::find(arr.begin(),arr.end(),"move")!=arr.end();
}

void Pet::move_update(float dt)
{
	const float distance = (owner->GetTransform().GetPosition() - GetTransform().GetPosition()).Length();
	if (distance <= 20.0f)return;

	const auto origin = GetTransform().GetPosition();

	GetTransform().SetPosition(origin + (owner->GetTransform().GetPosition() - GetTransform().GetPosition()).Normalised()*1.0f);
}

