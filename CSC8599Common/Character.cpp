#include "pch.h"
#include "Character.h"

#include "../Common/Assets.h"
#include "State.h"
#include "StateMachinePlus.h"
#include "EventSystem.h"
#include "StateTransition.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"


NCL::CSC8599::Character::Character()
	:state_machine_(nullptr),
	target(nullptr),
	user_controller_(new UserController()),
	timer(new GameTimer)
{
	init_state_machine();
}
void NCL::CSC8599::Character::update(float dt)
{
	user_controller_->update(dt);
	state_machine_->Update(dt);
}
std::string NCL::CSC8599::Character::print()
{
	std::string buffer;
	buffer += "Health:" + std::to_string(get_attr("health")._int) + "\n";
	buffer += state_machine_->Print(0);
	return buffer;
}

void NCL::CSC8599::Character::get_damage(const int source_id,const int damage)
{
	auto data = get_attr("health");
	auto health = data._int;
	health = health - damage <= 0 ? 0 : health - damage;
	data._int = health;
	set_attr("health", data);
	EventSystem::getInstance()->PushEvent("on_hit", 2, std::to_string(source_id).c_str(),std::to_string(worldID).c_str());
}

bool Character::switch_target(const int target_id)
{
	const auto temp=GameWorld::Get()->find_game_object(target_id);
	if (!temp)return false;
	if (target && target->GetWorldID() == temp->GetWorldID())return false;
	target = temp;
	EventSystem::getInstance()->PushEvent("ThreatChanged", 2, std::to_string(target->GetWorldID()).c_str(),std::to_string(GetWorldID()).c_str());
	return true;
}

bool Character::switch_nearest_target()
{
	const auto temp = GameWorld::Get()->find_nearest_game_object(this);
	if (!temp)return false;
	target = temp;
	EventSystem::getInstance()->PushEvent("ThreatChanged", 2, std::to_string(target->GetWorldID()).c_str(),std::to_string(GetWorldID()).c_str());
	return true;
}

void Character::UI_update(const Matrix4& viewMatrix, const Matrix4 projectMatrix)
{
	showHUD(viewMatrix,projectMatrix,name,5.f);
	showHUD(viewMatrix, projectMatrix, std::to_string(get_attr("health")._int), 7.f);
	if(isSelected)
		showHUD(viewMatrix, projectMatrix, "[Focus]", 12.f,Vector4(1,1,0,1));
}

bool Character::isAlive()
{
	return get_attr("health")._int>0;
}

data NCL::CSC8599::Character::get_attr(const std::string& attr_name)
{
	const auto result = attrs_.find(attr_name);
	if (result == attrs_.end())return { 0 };
	return result->second;
}
void NCL::CSC8599::Character::set_attr(const std::string& attr_name,const data data)
{
	attrs_[attr_name] = data;
}
void NCL::CSC8599::Character::init_attrs(const std::string& attr_file_name)
{
	std::ifstream t(NCL::Assets::DATADIR + attr_file_name);
	rapidjson::IStreamWrapper isw(t);
	rapidjson::Document document;
	document.ParseStream(isw);
	for (rapidjson::Document::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
	{
		if (itr->value.IsString())
		{
			const char* source = itr->value.GetString();
			name = std::string(source);
		}
		if (itr->value.IsInt())attrs_[itr->name.GetString()]._int = itr->value.GetInt();
		if (itr->value.IsFloat())attrs_[itr->name.GetString()]._float = itr->value.GetFloat();
		if (itr->value.IsBool())attrs_[itr->name.GetString()]._bool = itr->value.GetBool();
	}
}

void NCL::CSC8599::Character::init_state_machine()
{
	const auto attack = new State([this](float dt)->void { return attack_update(dt); });
	const auto prepare = new State([this](float dt)->void { return prepare_update(dt); });

	const auto actions = new StateMachine("prepare", prepare);
	actions->AddComponent("attack", attack);
	actions->AddTransition(new CSC8599::StateTransition(attack, prepare,
		[this](EVENT* event)->bool {return attack_to_prepare(); }, ""));
	actions->AddTransition(new CSC8599::StateTransition(prepare, attack,
		[this](EVENT* event)->bool {return prepare_to_attack(); }, ""));

	const auto move = new State([this](float dt)->void { return move_update(dt); });
	const auto stand = new State([this](float dt)->void { return stand_update(dt); });
	const auto movement = new StateMachine("stand", stand);
	movement->AddComponent("move", move);
	movement->AddTransition(new CSC8599::StateTransition(move, stand,
		[this](EVENT* event)->bool {return move_to_stand(); }, ""));
	movement->AddTransition(new CSC8599::StateTransition(stand, move,
		[this](EVENT* event)->bool {return stand_to_move(); }, ""));

	const auto model = new StateMachinePlus;
	model->AddComponent("actions", actions);
	model->AddComponent("movement", movement);

	const auto alive = new StateMachinePlus;
	alive->AddComponent("model", model);

	const auto dead = new State([this](float dt)->void { return dead_update(dt); });
	state_machine_ = new StateMachine("alive", alive);
	state_machine_->AddComponent("dead", dead);
	state_machine_->AddTransition(new CSC8599::StateTransition(alive, dead,
		[this](EVENT* event)->bool {return alive_to_dead(); }, ""));
}

void Character::showHUD(const Matrix4& viewMatrix, const Matrix4 projectMatrix, std::string text, const float height, Vector4 color)
{
	Matrix4 local = GetTransform().GetMatrix();
	local.SetPositionVector({ 0, 0, 0 });

	Vector3 up = local * Vector4(0, 1, 0, 1.0f);
	Vector3 left = local * Vector4(-1, 0, 0, 1.0f);
	Vector3 worldPos = GetTransform().GetPosition();
	Vector3 clip = projectMatrix * viewMatrix * worldPos;
	Vector2 canvas;
	canvas.x = (clip.x + 2.0f) * 25.0f - 1.0f * text.size();
	canvas.y = (1.0f - clip.y) * 50.0f - height;
	Debug::Print(text, canvas,color);
}

bool NCL::CSC8599::Character::attack_to_prepare()
{
	if (target == nullptr)return false;
	const auto _target = dynamic_cast<Character*>(target);
	if (!_target)return false;
	return  !_target->isAlive()|| user_controller_->get_inputs().buttons[STOP];
}

bool Character::prepare_to_attack()
{
	if (target == nullptr)return false;
	const auto _target = dynamic_cast<Character*>(target);
	if (!_target)return false;
	return _target->isAlive() && user_controller_->get_inputs().buttons[ATTACK];
}

bool Character::alive_to_dead()
{
	return !isAlive();
}

bool Character::move_to_stand()
{
	return user_controller_->get_inputs().buttons[STOP];
}

bool Character::stand_to_move()
{
	return user_controller_->get_inputs().movement_direction!=Vector2();
}

void Character::attack_update(float dt)
{
	if (target == nullptr)return;
	const auto _target = dynamic_cast<Character*>(target);
	if (!_target)return;
	if (!_target->isAlive())return;
	attack_time += dt;
	if (attack_time <= 0.1f)return;
	attack_time = 0.0f;
	_target->get_damage(GetWorldID(), get_attr("damage")._int);
}

void Character::prepare_update(float dt)
{
}

void Character::move_update(float dt)
{
}

void Character::stand_update(float dt)
{
}

void Character::dead_update(float dt)
{
}
