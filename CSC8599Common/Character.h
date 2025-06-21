#pragma once
#include "../CSC8503/CSC8503Common/GameObject.h";
#include "../Common/UserController.h"
#include "StateMachine.h"

namespace NCL
{
	class GameTimer;
}

using namespace NCL::CSC8503;
namespace NCL {
	namespace CSC8599 {
		union data
		{
			int _int;
			float _float;
			bool _bool;
		};
		class Pet;
		class Character :public GameObject
		{
			friend class UserController;
		public:
			Character();
			~Character() override = default;
			void update(float dt) override;
			data get_attr(const std::string& attr_name);
			void set_attr(const std::string& attr_name, const data data);
			std::string print();
			virtual void get_damage(const int source_id, const int damage);
			bool switch_target(const int target_id);
			bool switch_nearest_target();
			void UI_update(const Matrix4& viewMatrix, const Matrix4 projectMatrix) override;
			StateMachine* get_state_machine()const { return state_machine_; }
			GameObject* get_target()const { return target; }
			bool isAlive();
			void set_user_controller(UserController* controller) { user_controller_ = controller; }
		protected:
			StateMachine* state_machine_;
			std::map<std::string, data> attrs_;
			UserController* user_controller_;
			GameObject* target;

			GameTimer* timer;
			
			float attack_time = 0.f;
			void init_attrs(const std::string& attr_file_name);
			void init_state_machine();
			void showHUD(const Matrix4& viewMatrix, const Matrix4 projectMatrix,std::string text,const float height,Vector4 color=Vector4(1,1,1,1));
			virtual bool attack_to_prepare();
			virtual bool prepare_to_attack();
			virtual bool alive_to_dead();
			virtual bool move_to_stand();
			virtual bool stand_to_move();

			virtual void attack_update(float dt);
			virtual void prepare_update(float dt);
			virtual void move_update(float dt);
			virtual void stand_update(float dt);
			virtual void dead_update(float dt);


		};
	}
}
