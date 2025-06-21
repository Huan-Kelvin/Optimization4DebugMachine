#include "pch.h"
#include "Dragon.h"
#include "EventSystem.h"
bool NCL::CSC8599::Dragon::alive_to_dead()
{
	const auto result = isAlive();
	if (!result)
		EventSystem::getInstance()->PushEvent("dragon_die", 1, std::to_string(GetWorldID()).c_str());
	return !result;
}
bool NCL::CSC8599::Dragon::move_to_stand()
{
	const auto _distance = (GetTransform().GetPosition() - destination).Length();
	if (_distance <= 1.0f)
	{
		EventSystem::getInstance()->PushEvent("arrival", 0);
		return true;
	}
	return false;
}

bool NCL::CSC8599::Dragon::stand_to_move()
{
	const auto distance = (owner->GetTransform().GetPosition()
		- GetTransform().GetPosition()).Length();
	const auto _distance = (GetTransform().GetPosition() - destination).Length();
	return _distance >1.0f&&distance<20.0f;
}

void NCL::CSC8599::Dragon::move_update(float dt)
{
	time_stack += dt;
	if (time_stack > 0.1f)
	{
		const auto origin = GetTransform().GetPosition();
		GetTransform().SetPosition(origin + (destination - GetTransform().GetPosition()).Normalised() * 1.0f);
		time_stack = 0.0f;
	}
}
