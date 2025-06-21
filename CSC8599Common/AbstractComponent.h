#pragma once
#include <string>
#include <vector>

namespace NCL {
	namespace CSC8599 {
		class AbstractComponent
		{
		public:
			AbstractComponent() = default;
			virtual~AbstractComponent() = default;
			virtual void Update(float dt) = 0;
			virtual std::string Print(int index) = 0;
			virtual void GetActiveComponentArr(std::vector<std::string>& arr)=0;
		};
	}
}
