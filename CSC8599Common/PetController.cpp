#include "pch.h"
#include "PetController.h"
#include "../Common/Window.h"
void NCL::CSC8599::PetController::update(const float dt)
{
	clear_input();
	const auto keyboard = Window::GetKeyboard();
	if (keyboard->KeyHeld(KeyboardKeys::N)) last_input_.buttons[ATTACK] = true;
	if (keyboard->KeyHeld(KeyboardKeys::M)) last_input_.buttons[STOP] = true;
}
