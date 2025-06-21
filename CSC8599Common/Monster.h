#pragma once
#include "Character.h"
#include "StateMachine.h"
namespace NCL {
	namespace CSC8599
	{
		class Monster:public Character
		{
		public:
			Monster();
			void get_damage(const int source_id, const int damage) override;
			void get_taunt(const int source_id);
			void update(float dt) override;
			bool immortal = false;

			StateMachine* get_monster_state_machine() const
			{
				return monster_state_machine;
			}
			bool useStateMachine = true;

		private:
			void attack_update(float dt) override;
			std::map<int,int> ThreatMap;
			StateMachine* monster_state_machine = nullptr;
			void init_state_machine();
			float time_stack = 0.0f;
		protected:
			bool prepare_to_attack() override;
			bool move_to_stand() override;
			bool stand_to_move() override;
			void move_update(float dt) override;
			bool alive_to_dead() override;
			Character* pet = nullptr;
		public:
			void set_pet(Character* pet)
			{
				this->pet = pet;
			}
		};
	}
}

