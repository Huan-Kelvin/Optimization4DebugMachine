#pragma once
#include "CollisionVolume.h"

namespace NCL {
	class SphereVolume : CollisionVolume
	{
	public:
		SphereVolume(float sphereRadius = 1.0f) {
			type	= VolumeType::Sphere;
			radius	= sphereRadius;
		}
		~SphereVolume() {}

		float GetRadius() const {
			return radius;
		}
	protected:
		float	radius;//没有存储位置是因为 我们会把位置存在Transfrom类中 成为GameObject的一部分
	};
}

