#pragma once
#include <vector>
#include "Ray.h"
#include "CollisionDetection.h"
#include "QuadTree.h"
/*
游戏世界总览，增加和减少游戏物体等等
*/
namespace NCL {
		class Camera;
		using Maths::Ray;
	namespace CSC8503 {
		class GameObject;
		class Constraint;

		typedef std::function<void(GameObject*)> GameObjectFunc;
		typedef std::vector<GameObject*>::const_iterator GameObjectIterator;

		class GameWorld	{
		public:
			GameWorld();
			~GameWorld();

			void Clear();
			void ClearAndErase();

			void AddGameObject(GameObject* o);
			void RemoveGameObject(GameObject* o, bool andDelete = false);

			void AddConstraint(Constraint* c);
			void RemoveConstraint(Constraint* c, bool andDelete = false);

			Camera* GetMainCamera() const {
				return mainCamera;
			}

			void ShuffleConstraints(bool state) {
				shuffleConstraints = state;
			}

			void ShuffleObjects(bool state) {
				shuffleObjects = state;
			}
			/// <summary>
			/// 计算游戏场景中所有的物体是否与提供的射线碰撞
			/// </summary>
			/// <param name="r">射线</param>
			/// <param name="closestCollision">最近的碰撞发生的位置</param>
			/// <param name="closestObject">是否选择最近的碰撞到的物体</param>
			/// <returns>是否发生碰撞</returns>
			bool Raycast(Ray& r, RayCollision& closestCollision, bool closestObject = false) const;
			/// <summary>
			/// 和UpdateScene一样 更新所有在游戏世界中的节点 
			/// 渲染对象会利用这个类来创造渲染队列
			/// 物理对象会利用这个类来创造物理计算队列
			/// </summary>
			/// <param name="dt">时间步数</param>
			virtual void UpdateWorld(float dt);

			void OperateOnContents(GameObjectFunc f);

			void GetObjectIterators(
				GameObjectIterator& first,
				GameObjectIterator& last) const;

			void GetConstraintIterators(
				std::vector<Constraint*>::const_iterator& first,
				std::vector<Constraint*>::const_iterator& last) const;
			static GameWorld* Get(){
				return  p_self;
			}
			static GameWorld* p_self;
			GameObject* find_game_object(int id) ;
			GameObject* find_nearest_game_object(GameObject* origin) const ;
		protected:
			std::vector<GameObject*> gameObjects;
			std::vector<Constraint*> constraints;

			Camera* mainCamera;

			bool	shuffleConstraints;
			bool	shuffleObjects;
			int		worldIDCounter;
		};
	}
}

