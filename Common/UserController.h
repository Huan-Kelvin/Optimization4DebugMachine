#pragma once
#include "Vector2.h"
enum Buttons
{
	ATTACK,
	STOP,
	PAUSE,
	SWITCH_TARGET,
	SWITCH_PET_MODEL,
	MAX_INPUT
};

struct Input {
	bool buttons[MAX_INPUT] = { false };
	NCL::Maths::Vector2 look_direction = NCL::Maths::Vector2();
	NCL::Maths::Vector2 movement_direction = NCL::Maths::Vector2();
};

class UserController
{
public:
	UserController() = default;
	UserController(const UserController&) = delete;
	UserController& operator=(const UserController&) = delete;

	UserController(UserController&&) = delete;
	UserController& operator=(const UserController&&) = delete;

	virtual ~UserController() = default;
	Input get_inputs() { return last_input_; }
	virtual void update(const float dt) {}
	int random(int low, int high);
protected:
	Input last_input_;
	void clear_input() { last_input_ = {}; }
};