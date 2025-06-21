#include "pch.h"
#include "Player.h"
#include "PlayerController.h"
#include "../CSC8503/CSC8503Common/Debug.h"
#include "EventSystem.h"
#include "Pet.h"
NCL::CSC8599::Player::Player()
{
	user_controller_ = new PlayerController();
	init_attrs("player.json");
	EventSystem::getInstance()->RegisterEventHandler("ThreatChanged", [this](EVENT* p_event)->void
		{
			const int id = std::stoi(p_event->vArg[0]);
			const int source = std::stoi(p_event->vArg[1]);
		if(id==GetWorldID())
		{
			EventSystem::getInstance()->PushEvent("player_over_threat", 0);
		}
		});
}

void NCL::CSC8599::Player::move_update(float dt)
{
	const auto input=user_controller_->get_inputs();
	const auto origin = GetTransform().GetPosition();
	if (input.movement_direction == Vector2(1, 0))
		GetTransform().SetPosition(origin+Vector3(1, 0, 0));
	if (input.movement_direction == Vector2(-1, 0))
		GetTransform().SetPosition(origin + Vector3(-1, 0, 0));
	if (input.movement_direction == Vector2(0, 1))
		GetTransform().SetPosition(origin + Vector3(0, 0, -1));
	if (input.movement_direction == Vector2(0, -1))
		GetTransform().SetPosition(origin + Vector3(0, 0, 1));
}

bool NCL::CSC8599::Player::alive_to_dead()
{
	const auto result = Character::alive_to_dead();
	if (result)EventSystem::getInstance()->PushEvent("player_die", 1, std::to_string(GetWorldID()).c_str());
	return result;
}

bool NCL::CSC8599::Player::prepare_to_attack()
{
	return Character::prepare_to_attack()&&target->GetWorldID()!=pet->GetWorldID();
}

void NCL::CSC8599::Player::update(float dt)
{
	Character::update(dt);
	if (user_controller_->get_inputs().buttons[SWITCH_TARGET])
		switch_nearest_target();
	if (target)
		target->isSelected = true;
	if (user_controller_->get_inputs().buttons[SWITCH_PET_MODEL])
	{
		const auto temp = dynamic_cast<Pet*>(pet);
		if(static_cast<int>(temp->get_model())+1== static_cast<int>(ControlModelType::MAX))
		{
			temp->set_model(static_cast<ControlModelType>(0));
		}
		else
		{
			temp->set_model(static_cast<ControlModelType>(static_cast<int>(temp->get_model())+1));
		}
	}

	//auto _target = dynamic_cast<Character*>(target);
	//if(_target)
	//{
	//	auto _target_target = _target->get_target();
	//	if(_target_target)
	//	{
	//		if(_target_target->GetWorldID()==GetWorldID())
	//			EventSystem::getInstance()->PushEvent("player_over_threat", 0);
	//	}
	//}
}


