#pragma once
#include "../Common/UserController.h"
#include "Player.h"
namespace NCL {
	namespace CSC8599 {
		class PlayerAIController :public UserController {
			friend class Player;
		public:
			PlayerAIController(Player* obj):object(obj){}
			void update(const float dt) override;
		private:
			Player* object;
		};
	}
}
