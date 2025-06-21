#pragma once
#include <functional>

#include "AbstractComponent.h"
namespace NCL {
	namespace CSC8599 {
		using  StateUpdateFunction = std::function<void(float)>;
		class State :public AbstractComponent
		{
		public:
			explicit State(StateUpdateFunction updateFunction) {
				func = std::move(updateFunction);
			}
			~State()override = default;
			void Update(float dt) override {
				if (func != nullptr)
					func(dt);
			}
			void GetActiveComponentArr(std::vector<std::string>& arr) override{};
			std::string Print(int index)override;
			int expectation=0;
		protected:
			StateUpdateFunction func;
		};
	}
}
