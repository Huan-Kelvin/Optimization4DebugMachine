#pragma once
#include "Character.h"
namespace NCL {
	namespace CSC8599
	{
		enum class ControlModelType {
			PASSIVE,
			ASSIST,
			PROTECT,
			MAX
		};
		class Pet:public Character
		{
		public:
			Pet(Character* _owner);
			void set_model(const ControlModelType type) { model = type; }
			void update(float dt) override;
			void UI_update(const Matrix4& viewMatrix, const Matrix4 projectMatrix) override;
			Character* owner = nullptr;
		protected:
			bool attack_to_prepare() override;
			bool prepare_to_attack() override;
			bool alive_to_dead() override;
			bool move_to_stand() override;
			bool stand_to_move() override;
			void move_update(float dt) override;
		public:
			ControlModelType get_model() const
			{
				return model;
			}

		private:
			ControlModelType model=ControlModelType::PASSIVE;
			
		};
	}
}

