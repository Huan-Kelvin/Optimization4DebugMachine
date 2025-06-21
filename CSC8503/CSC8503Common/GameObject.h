#pragma once
#include "Transform.h"
#include "CollisionVolume.h"

#include "PhysicsObject.h"
#include "RenderObject.h"

#include <vector>

using std::vector;
enum Layers
{
	Default,
	Water,
	UI,
	Player
};
namespace NCL {
	namespace CSC8503 {
		class GameObject {
		public:
			GameObject(string name = "");
			virtual ~GameObject();

			void SetBoundingVolume(CollisionVolume* vol) {
				boundingVolume = vol;
			}

			const CollisionVolume* GetBoundingVolume() const {
				return boundingVolume;
			}

			bool IsActive() const {
				return isActive;
			}

			Transform& GetTransform() {
				return transform;
			}

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			PhysicsObject* GetPhysicsObject() const {
				return physicsObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			void SetPhysicsObject(PhysicsObject* newObject) {
				physicsObject = newObject;
			}

			const string& GetName() const {
				return name;
			}

			virtual void OnCollisionBegin(GameObject* otherObject) {
				//std::cout << "OnCollisionBegin event occured!\n";
			}

			virtual void OnCollisionEnd(GameObject* otherObject) {
				//std::cout << "OnCollisionEnd event occured!\n";
			}

			bool GetBroadphaseAABB(Vector3& outsize) const;

			void UpdateBroadphaseAABB();

			void SetWorldID(int newID) {
				worldID = newID;
			}

			int		GetWorldID() const {
				return worldID;
			}

			Layers GetLayer() const { return layers; }

			void SetLayer(Layers l) { layers = l; }

			virtual void update(float dt){}
			virtual void UI_update(const Matrix4& viewMatrix, const Matrix4 projectMatrix){}
			bool isSelected = false;
		protected:
			Transform			transform;//提供物体的世界坐标，大小，本地和世界坐标变换矩阵

			CollisionVolume* boundingVolume;//定义物体的碰撞形态
			PhysicsObject* physicsObject;
			RenderObject* renderObject;

			bool	isActive;//决定物体是否存在于render和physics交互中
			int		worldID;
			string	name; //游戏对象的名字

			Vector3 broadphaseAABB;

			Layers layers;//游戏物体属于什么layer
			void register_handlers();

			
			
		};
	}
}
