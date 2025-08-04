#pragma once
#include "AbstractStateMachine.h"
#include <unordered_map>
#include "../CSC8503/CSC8503Common/GameObject.h"
#include <unordered_set>

using namespace NCL::CSC8503;
namespace NCL {
	namespace CSC8599 {
		class StateTransition;
		using TransitionContainer = std::multimap<AbstractComponent*, StateTransition*>;
		using TransitionIterator = TransitionContainer::iterator;
		using ActiveMapSM = std::unordered_map<AbstractStateMachine*, AbstractComponent*>;
		using ActiveMapObj = std::unordered_map<GameObject*, AbstractComponent*>;
		class SharedStateMachine : public AbstractStateMachine {
		public:
			SharedStateMachine(const std::string& name, AbstractComponent* defaultComponent, AbstractComponent* exp = nullptr)
				:expComponent(exp) {
				AddComponent(name, defaultComponent);
				enterComponent = defaultComponent;
			}
			~SharedStateMachine() = default;
			void Update(float dt) override;
			std::string Print(int index) override;
			void AddTransition(StateTransition* t);
			void GetActiveComponentArr(std::vector<std::string>& arr) override;
			void GetActiveComponentArr(AbstractStateMachine* machine, std::vector<std::string>& arr);
			void GetActiveComponentArr(GameObject* object, std::vector<std::string>& arr);
			void SetActiveComponent(AbstractStateMachine* machine, AbstractComponent* active)
			{
				activeComponentsSM[machine] = active;
			}
			void SetActiveComponent(GameObject* object, AbstractComponent* active)
			{
				activeComponentsObj[object] = active;
			}
			TransitionContainer get_all_transitions() const
			{
				return allTransitions;
			}

			ActiveMapSM& get_active_component_sm()
			{
				return activeComponentsSM;
			}
			ActiveMapObj& get_active_component_obj()
			{
				return activeComponentsObj;
			}

			string GetCurStateName(GameObject* obj)
			{
				for (const auto& t : activeComponentsObj)
				{
					if (t.first == obj)
					{
						return GetStateName(t.second);
					}
				}
				return "UnknownStateName";
			}

			AbstractComponent* get_exp_component() const
			{
				return expComponent;
			}
			std::pair<TransitionIterator, TransitionIterator> get_transitions(AbstractComponent* state);

			void AddStatemachine(AbstractStateMachine* machine) {
				activeComponentsSM[machine] = enterComponent;
			}
			void AddStatemachine(GameObject* object) {
				//std::cout << "AddStatemachine called with object ptr: " << object << std::endl;
				activeComponentsObj[object] = enterComponent;
			}
			bool IsActive(AbstractStateMachine* machine) const {
				return activeComponentsSM.find(machine) != activeComponentsSM.end();
			}
			bool IsActive(GameObject* object) const {
				return activeComponentsObj.find(object) != activeComponentsObj.end();
			}

			GameObject* GetCurUpdateObject() const { return updatingObject; }

			void BlockObject(GameObject* obj) { blocks.insert(obj); }
			void TempReset(GameObject* obj) { activeComponentsObj[obj] = enterComponent; }

		protected:
			ActiveMapSM  activeComponentsSM;
			ActiveMapObj  activeComponentsObj;

			AbstractComponent* expComponent;
			TransitionContainer allTransitions;

			AbstractComponent* enterComponent;

			GameObject* updatingObject = nullptr;

			std::unordered_set<GameObject*> blocks;
		};
	}
}