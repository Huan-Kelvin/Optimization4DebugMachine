#pragma once
#include "pch.h"
#include "EventSystem.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"
#include "State.h"
#include "StateTransition.h"
#include "ExtendCharacter.h"
#include "SharedStateMachine.h"

using namespace NCL;
using namespace CSC8503;
using namespace CSC8599;

ExtendCharacter::ExtendCharacter(CharacterType* parentType, string name) :GameObject(name) {
	typeObject = parentType;

	typeObject->GetStateMachine()->AddStatemachine(this);

	curHealth = typeObject->GetMaxHealth();

	GameWorld::Get()->AddGameObject(this);
}

void ExtendCharacter::update(float dt)
{
	typeObject->showHUD(transform, name, 15);
	typeObject->showHUD(transform, GetStateMachine()->GetCurStateName(this), 12);
	typeObject->showHUD(transform, std::to_string(static_cast<int>(curHealth)), 9);
}

SharedStateMachine* ExtendCharacter::GetStateMachine() const {
	return typeObject->GetStateMachine();
}

void ExtendCharacter::BlockTrans() {
	typeObject->BlockTrans(this);
}

void ExtendCharacter::TakeDamage(float damage, string source) {
	typeObject->takeDamage(this, damage, GameWorld::Get()->find_game_object(source));
}