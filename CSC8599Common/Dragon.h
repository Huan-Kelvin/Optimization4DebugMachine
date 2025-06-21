#pragma once
#include "Pet.h"
namespace NCL {
	namespace CSC8599
	{
		class Dragon:public Pet
		{
		public:
			explicit Dragon(Character* _owner)
				: Pet(_owner)
			{
				init_attrs("dragon.json");
			}

		protected:
			bool alive_to_dead() override;
			bool move_to_stand() override;
			bool stand_to_move() override;
			void move_update(float dt) override;
		private:
			float time_stack = 0.0f;
			Vector3 destination = Vector3(-30,15 , 0);
		};
	}
}


