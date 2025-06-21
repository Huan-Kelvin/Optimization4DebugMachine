#pragma once
#include "../../Common/Vector3.h"
#include "../../Common/Plane.h"
#include "../../CSC8503/CSC8503Common/GameObject.h"
namespace NCL {
	namespace Maths {
		struct RayCollision {
			void*		node;			//Node that was hit 这条射线有可能会和任意类型的物体碰撞
			Vector3		collidedAt;		//WORLD SPACE position of the collision!
			float		rayDistance;

			RayCollision() {
				node			= nullptr;
				rayDistance		= FLT_MAX;
			}
		};

		class Ray {
		public:
			Ray(Vector3 position, Vector3 direction,Layers layer=Default) {
				this->position  = position;
				this->direction = direction;
				this->layer = layer;
			}
			~Ray(void) {}

			Vector3 GetPosition() const {return position;	}

			Vector3 GetDirection() const {return direction;	}

			Layers GetLayer()const { return layer; }
			void SetLayer(Layers l) { layer = l; }
		protected:
			Vector3 position;	//World space position
			Vector3 direction;	//Normalised world space direction
			Layers layer; //射线的目标layer
		};
	}
}