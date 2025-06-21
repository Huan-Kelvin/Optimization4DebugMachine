#pragma once
#include "AbstractStateMachine.h"
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		class StateTransition;
		using TransitionContainer = std::multimap<AbstractComponent*, StateTransition*>;
		using TransitionIterator = TransitionContainer::iterator;
		class StateMachine : public AbstractStateMachine {
		public:
			StateMachine(const std::string& name, AbstractComponent* defaultComponent,AbstractComponent* exp=nullptr)
				:activeComponent(defaultComponent), expComponent(exp){
				AddComponent(name, defaultComponent);
			}
			~StateMachine() override { delete activeComponent; activeComponent = nullptr; }
			void Update(float dt) override;
			std::string Print(int index) override;
			void AddTransition(StateTransition* t);
			void GetActiveComponentArr(std::vector<std::string>& arr) override;
			void SetActiveComponent(AbstractComponent* active)
			{
				activeComponent = active;
			}
			TransitionContainer get_all_transitions() const
			{
				return allTransitions;
			}

			AbstractComponent* get_active_component() const
			{
				return activeComponent;
			}

			AbstractComponent* get_exp_component() const
			{
				return expComponent;
			}
			std::pair<TransitionIterator, TransitionIterator> get_transitions(AbstractComponent* state);
		protected:
			AbstractComponent* activeComponent;
			AbstractComponent* expComponent;
			TransitionContainer allTransitions;
		};
	}
}
