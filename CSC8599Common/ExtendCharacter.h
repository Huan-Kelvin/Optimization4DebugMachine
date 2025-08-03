#pragma once
#include "../CSC8503/CSC8503Common/GameObject.h"
#include "../CSC8503/CSC8503Common/Debug.h"
#include "StateMachine.h"
#include "SharedStateMachine.h"
#include "State.h"
#include "TypeObject.h"

namespace NCL {
	namespace CSC8599
	{
		class ExtendCharacter :public CSC8503::GameObject
		{
		public:
			ExtendCharacter(CharacterType* parentType, string name);
			void update(float dt) override;

			SharedStateMachine* GetStateMachine() const;

			void SetTag(string newTag) { tag = newTag; }

		private:
			CharacterType* typeObject = nullptr;

			string tag;
			float curHealth;
		};
	}
}