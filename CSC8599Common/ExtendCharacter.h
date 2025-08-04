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
		class TypeObject;
		class ExtendCharacter :public CSC8503::GameObject
		{
		public:
			ExtendCharacter(CharacterType* parentType, string name);
			void update(float dt) override;

			SharedStateMachine* GetStateMachine() const;

			void SetTag(string newTag) { tag = newTag; }

			void BlockTrans();

			void TakeDamage(float damage, string source = "");
			void HealthChange(float delta) { curHealth += delta; }
			void ResetHealth();
			float GetCurHealth() const { return curHealth; }
			
		private:
			CharacterType* typeObject = nullptr;

			string tag;
			float curHealth;
		};
	}
}