#pragma once
#include "PushdownState.h"
#include "../../Common/Window.h"
#include "PauseScreen.h"
#include <iostream>
using namespace NCL;
using namespace CSC8503;
class GameScreen:public PushdownState
{
	PushdownResult OnUpdate(float dt,
		PushdownState * *newState) override {
		pauseReminder -= dt;
		if (pauseReminder < 0) {
			std::cout << " Coins mined : " << coinsMined << "\n";
			std::cout << " Press P to pause game ,or F1 to return to main menu !\n";
			pauseReminder += 1.0f;
		}
		if (Window::GetKeyboard()-> KeyDown(KeyboardKeys::P)) {
			*newState = new PauseScreen();
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()-> KeyDown(KeyboardKeys::F1)) {
			std::cout << " Returning to main menu !\n";
			return PushdownResult::Pop;
		}
		if (rand() % 7 == 0) {
			coinsMined++;
		}
		return PushdownResult::NoChange;
	};
	void OnAwake() override {
		std::cout << " Preparing to mine coins !\n";
	}
protected:
	int coinsMined = 0;
	float pauseReminder = 1;
};

