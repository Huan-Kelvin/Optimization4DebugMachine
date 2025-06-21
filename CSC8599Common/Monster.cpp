#include "pch.h"
#include "Monster.h"
#include "EventSystem.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"
#include "State.h"
#include "StateTransition.h"
Monster::Monster()
{
	init_attrs("monster.json");
	init_state_machine();
}
bool cmp_value(const std::pair<int, int> left, const std::pair<int, int> right)
{
	return left.second < right.second;
}

void Monster::get_damage(const int source_id, const int damage)
{
	if(immortal)return;
	Character::get_damage(source_id, damage);
	ThreatMap[source_id] += damage;
}

void Monster::get_taunt(const int source_id)
{
	ThreatMap[source_id] = 999;
}

void NCL::CSC8599::Monster::update(float dt)
{
	Character::update(dt);
	if(useStateMachine)
		monster_state_machine->Update(dt);
}


void Monster::attack_update(float dt)
{
	const auto i = max_element(ThreatMap.begin(), ThreatMap.end(), cmp_value);
	if (i->second == 0)return;
	if(!target)
	{
		switch_target(i->first);
	}else
	{
		if (target->GetWorldID() != i->first)
		{
			switch_target(i->first);
		}
	}
	Character::attack_update(dt);
}



void NCL::CSC8599::Monster::init_state_machine()
{
	auto init = new State([this](float dt)->void
	{});
	auto summon=new State([this](float dt)->void
	{});
	auto ride = new State([this](float dt)->void
		{
			time_stack += dt;
			if (time_stack > 0.1f)
			{
				if (pet == nullptr)return;
				const auto origin = GetTransform().GetPosition();
				const auto distance = (origin - pet->GetTransform().GetPosition()).Length();
				if(distance>=20.0f)
					GetTransform().SetPosition(origin + (pet->GetTransform().GetPosition() - GetTransform().GetPosition()).Normalised() * 1.0f);
				time_stack = 0.0f;
			}
		});
	auto end = new State([this](float dt)->void
	{
		if(EventSystem::getInstance()->HasHappened("dragon_die"))
			immortal = false;
	});
	monster_state_machine = new StateMachine("init", init,end);
	monster_state_machine->AddComponent("summon", summon);
	monster_state_machine->AddComponent("ride",ride);
	monster_state_machine->AddComponent("end", end);
	monster_state_machine->AddTransition(new CSC8599::StateTransition(init, summon, [this](EVENT* event)->bool
		{
			auto health = get_attr("health")._int;
			if(health <= 30 && !pet)
			{
				immortal = true;
				EventSystem::getInstance()->PushEvent("summon_dragon", 1, std::to_string(GetWorldID()).c_str());
				return true;
			}
			return false;
		}, ""));
	monster_state_machine->AddTransition(new CSC8599::StateTransition(summon, ride, [this](EVENT* event)->bool
		{
			return pet;
		}, ""));
	monster_state_machine->AddTransition(new CSC8599::StateTransition(ride, end, [this](EVENT* event)->bool
		{
			return true;
		}, "arrival"));

}


bool Monster::prepare_to_attack()
{
	return !ThreatMap.empty();
}

bool Monster::move_to_stand()
{
	if (target == nullptr)return false;
	const float distance = (target->GetTransform().GetPosition() - GetTransform().GetPosition()).Length();
	return distance <= 10.0f;
}

bool Monster::stand_to_move()
{
	if (target == nullptr)return false;
	const float distance = (target->GetTransform().GetPosition() - GetTransform().GetPosition()).Length();
	return distance > 60.0f;
}

void Monster::move_update(float dt)
{
	if (target == nullptr)return;
	const auto origin = GetTransform().GetPosition();
	if(!pet)
	GetTransform().SetPosition(origin + (target->GetTransform().GetPosition() - GetTransform().GetPosition()).Normalised() * 1.0f);
}

bool Monster::alive_to_dead()
{
	const auto result = Character::alive_to_dead();
	if (result)EventSystem::getInstance()->PushEvent("MonsterDie", 1, std::to_string(GetWorldID()).c_str());
	return result;
}
