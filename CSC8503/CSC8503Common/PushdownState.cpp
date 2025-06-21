#include "PushdownState.h"

using namespace NCL::CSC8503;

PushdownState::PushdownState()
{
}


PushdownState::~PushdownState()
{
}

PushdownState::PushdownResult PushdownState::OnUpdate(float dt,PushdownState** pushResult) {

	return PushdownResult::NoChange;
}