#pragma once
#include "../Common/UserController.h"
namespace NCL {
	namespace CSC8599 {
		class PetController :public UserController {
		public:
			void update(const float dt) override;
		};
	}
}

