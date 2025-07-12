#pragma once
#include "AbstractStateMachine.h"
#include <unordered_map>

namespace NCL {
	namespace CSC8599 {
		class StateTransition;
		using TransitionContainer = std::multimap<AbstractComponent*, StateTransition*>;
		using TransitionIterator = TransitionContainer::iterator;
		using ActiveMap = std::unordered_map<AbstractStateMachine*, AbstractComponent*>;
		class SharedStateMachine : public AbstractStateMachine {
		public:
			SharedStateMachine(const std::string& name, AbstractComponent* defaultComponent, AbstractComponent* exp = nullptr)
				:expComponent(exp) {
				AddComponent(name, defaultComponent);
			}
			~SharedStateMachine() = default;
			void Update(float dt) override;
			std::string Print(int index) override;
			void AddTransition(StateTransition* t);
			void GetActiveComponentArr(std::vector<std::string>& arr) override;
			void GetActiveComponentArr(AbstractStateMachine* machine, std::vector<std::string>& arr);
			void SetActiveComponent(AbstractStateMachine* machine, AbstractComponent* active)
			{
				activeComponent[machine] = active;
			}
			TransitionContainer get_all_transitions() const
			{
				return allTransitions;
			}

			ActiveMap& get_active_component()
			{
				return activeComponent;
			}

			AbstractComponent* get_exp_component() const
			{
				return expComponent;
			}
			std::pair<TransitionIterator, TransitionIterator> get_transitions(AbstractComponent* state);
		protected:
			ActiveMap  activeComponent;
			AbstractComponent* expComponent;
			TransitionContainer allTransitions;
		};
	}
}