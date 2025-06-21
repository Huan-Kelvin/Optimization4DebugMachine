#pragma once
#include "PushdownState.h"
#include "../../Common/Window.h"
#include "PauseScreen.h"
#include "GameScreen.h"
#include <iostream>
class IntroScreen : public PushdownState
{
	PushdownResult OnUpdate(float dt,
		PushdownState** newState) override {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
			*newState = new GameScreen();
			return PushdownResult::Push;

		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
			return PushdownResult::Pop;

		}
		return PushdownResult::NoChange;
	};

	void OnAwake() override {
		std::cout << " Welcome to a really awesome game !\n";
		std::cout << " Press Space To Begin or escape to quit !\n";
	}
};

