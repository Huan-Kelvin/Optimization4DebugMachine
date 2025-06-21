#pragma once
#include "Character.h"
namespace NCL {
	namespace CSC8599
	{
		class Player :public Character
		{
		public:
			Player();
			void update(float dt) override;
			Character* get_pet() const
			{
				return pet;
			}
			void set_pet(Character* _pet)
			{
				this->pet = _pet;
			}
		private:
			void move_update(float dt) override;
		protected:
			bool alive_to_dead() override;
			bool prepare_to_attack() override;
			Character* pet = nullptr;
		};
	}
}
;
