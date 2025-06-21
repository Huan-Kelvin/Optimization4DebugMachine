#pragma once
#include "Constraint.h"
#include "../../Common/Vector3.h"
#include "GameObject.h"
using namespace NCL;
using namespace CSC8503;
using namespace Maths;
class PositionConstraint :public Constraint
{
public:
	PositionConstraint(GameObject* a, GameObject* b, float d) {
		objectA = a;
		objectB = b;
		distance = d;
	
	}
	~PositionConstraint() {}

	void UpdateConstraint(float dt) override {
		Vector3 relativePos = objectA->GetTransform().GetPosition() -
			objectB->GetTransform().GetPosition();
		float currentDistance = relativePos.Length();

		float offset = distance - currentDistance;// contraint= 约束条件-现在的距离

		if (abs(offset) > 0.0f) {//在最大的约束距离中   
			Vector3 offsetDir = relativePos.Normalised();//相对的方向

			PhysicsObject* physA = objectA->GetPhysicsObject();
			PhysicsObject* physB = objectB->GetPhysicsObject();

			Vector3 relativeVelocity = physA->GetLinearVelocity() - physB->GetLinearVelocity();//相对的速度

			float constraintMass = physA->GetInverseMass() + physB->GetInverseMass();//总质量inverse

			if (constraintMass > 0.0f) {
				float velocityDot = Vector3::Dot(relativeVelocity, offsetDir);   //C=J*v  如果要求派生的约束用jacobian来满足位置的约束 实际上是计算出了速度的约束
				float biasFactor = 0.01f;
				float bias = -(biasFactor / dt) * offset;

				float lambad = -(velocityDot + bias) / constraintMass;//拉格朗日算子           lambad=1/inverseMass*Jacobian*velocity

				Vector3 aImpulse = offsetDir * lambad;//力
				Vector3 bImpulse = -offsetDir * lambad;

				physA->ApplyLinearImpulse(aImpulse);
				physB->ApplyLinearImpulse(bImpulse);

			}
		}

	}
protected:
	GameObject* objectA;//前一个需要加入约束的物体
	GameObject* objectB;//后一个需要加入约束的物体
	float distance;//位置需要满足的约束

};



