#pragma once

#include "../../Common/Camera.h"
#include "../../Common/Plane.h"

#include "Transform.h"
#include "GameObject.h"

#include "AABBVolume.h"
#include "OBBVolume.h"
#include "SphereVolume.h"
#include "CapsuleVolume.h"
#include "Ray.h"

using NCL::Camera;
using namespace NCL::Maths;
using namespace NCL::CSC8503;
namespace NCL {
	class CollisionDetection
	{
	public:
		struct ContactPoint {
			Vector3 localA; //分离了contact point的概念 用法向量 渗透多少 
			Vector3 localB;
			Vector3 normal;
			float	penetration;
		};
		struct CollisionInfo {
			GameObject* a;
			GameObject* b;		
			mutable int		framesLeft;

			ContactPoint point;

			void AddContactPoint(const Vector3& localA, const Vector3& localB, const Vector3& normal, float p) {
				point.localA		= localA;
				point.localB		= localB;
				point.normal		= normal;
				point.penetration	= p;
			}

			//Advanced collision detection / resolution
			bool operator < (const CollisionInfo& other) const {
				size_t otherHash = (size_t)other.a->GetWorldID() + ((size_t)other.b->GetWorldID() << 32);
				size_t thisHash  = (size_t)a->GetWorldID()		 + ((size_t)b-> GetWorldID() << 32);

				if (thisHash < otherHash) {
					return true;
				}
				return false;
			}

			bool operator ==(const CollisionInfo& other) const {
				if (other.a == a && other.b == b) {
					return true;
				}
				return false;
			}
		};

		static bool SphereCapsuleIntersection(
			const CapsuleVolume& volumeA, const Transform& worldTransformA,
			const SphereVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo);

		//TODO ADD THIS PROPERLY

		/// <summary>
		/// 计算四面体碰撞的基础方法
		/// </summary>
		/// <param name="r">射线</param>
		/// <param name="boxPos">碰撞体的位置</param>
		/// <param name="boxSize">碰撞体的半径</param>
		/// <param name="collision">碰撞信息</param>
		/// <returns></returns>
		static bool RayBoxIntersection(const Ray&r, const Vector3& boxPos, const Vector3& boxSize, RayCollision& collision);

		static Ray BuildRayFromMouse(const Camera& c);
		/// <summary>
		/// 根据传入游戏物体的碰撞体类型选择对应的计算碰撞的方式
		/// </summary>
		/// <param name="r">射线</param>
		/// <param name="object">用于检测的游戏目标</param>
		/// <param name="collisions">用来存放碰撞的结果，包括了碰撞到的物体，碰撞的位置等等</param>
		/// <returns>返回检查是否成功</returns>
		static bool RayIntersection(const Ray&r, GameObject& object, RayCollision &collisions);

		/// <summary>
		/// AABB BOX碰撞分支
		/// </summary>
		/// <param name="r"></param>
		/// <param name="worldTransform"></param>
		/// <param name="volume"></param>
		/// <param name="collision"></param>
		/// <returns></returns>
		static bool RayAABBIntersection(const Ray&r, const Transform& worldTransform, const AABBVolume&	volume, RayCollision& collision);
		/// <summary>
		/// OBB BOX碰撞分支
		/// </summary>
		/// <param name="r"></param>
		/// <param name="worldTransform"></param>
		/// <param name="volume"></param>
		/// <param name="collision"></param>
		/// <returns></returns>
		static bool RayOBBIntersection(const Ray&r, const Transform& worldTransform, const OBBVolume&	volume, RayCollision& collision);
		/// <summary>
		/// 计算球体的碰撞
		/// </summary>
		/// <param name="r">射线</param>
		/// <param name="worldTransform">物体的世界坐标</param>
		/// <param name="volume">碰撞体的体积</param>
		/// <param name="collision">碰撞的结果</param>
		/// <returns>返回检查是否成功</returns>
		static bool RaySphereIntersection(const Ray&r, const Transform& worldTransform, const SphereVolume& volume, RayCollision& collision);
		static bool RayCapsuleIntersection(const Ray& r, const Transform& worldTransform, const CapsuleVolume& volume, RayCollision& collision);


		static bool RayPlaneIntersection(const Ray&r, const Plane&p, RayCollision& collisions);

		static bool	AABBTest(const Vector3& posA, const Vector3& posB, const Vector3& halfSizeA, const Vector3& halfSizeB);

		/// <summary>
		/// 输入两个游戏物体 决定他们是否碰撞 
		/// </summary>
		/// <param name="a">第一个物体</param>
		/// <param name="b">第二个物体</param>
		/// <param name="collisionInfo">碰撞的信息</param>
		/// <returns>是否碰撞</returns>
		static bool ObjectIntersection(GameObject* a, GameObject* b, CollisionInfo& collisionInfo);


		static bool AABBIntersection(	const AABBVolume& volumeA, const Transform& worldTransformA,
										const AABBVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo);

		static bool SphereIntersection(	const SphereVolume& volumeA, const Transform& worldTransformA,
										const SphereVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo);

		static bool AABBSphereIntersection(	const AABBVolume& volumeA	 , const Transform& worldTransformA,
										const SphereVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo);

		static bool OBBIntersection(	const OBBVolume& volumeA, const Transform& worldTransformA,
										const OBBVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo);

		static Vector3 Unproject(const Vector3& screenPos, const Camera& cam);

		static Vector3		UnprojectScreenPosition(Vector3 position, float aspect, float fov, const Camera &c);
		static Matrix4		GenerateInverseProjection(float aspect, float fov, float nearPlane, float farPlane);
		static Matrix4		GenerateInverseView(const Camera &c);

	protected:
	
	private:
		CollisionDetection()	{}
		~CollisionDetection()	{}
	};
}

