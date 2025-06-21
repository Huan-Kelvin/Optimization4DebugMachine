#include "pch.h"
#include "PlalyerAIController.h"

void NCL::CSC8599::PlayerAIController::update(const float dt)
{
	clear_input();
	const auto result = random(0, 100);

	//if (result==0) last_input_.movement_direction = Vector2(-1, 0);
	//if (result == 1) last_input_.movement_direction = Vector2(1, 0);
	//if (result == 2) last_input_.movement_direction = Vector2(0, 1);
	//if (result == 3) last_input_.movement_direction = Vector2(0, -1);
	if (result == 4) last_input_.buttons[SWITCH_TARGET] = true;
	if (result == 5) last_input_.buttons[SWITCH_PET_MODEL] = true;
	if (result == 6) last_input_.buttons[ATTACK] = true;
}
