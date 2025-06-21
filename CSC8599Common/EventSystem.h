#pragma once
#include "AbstractStateMachine.h"
#include <list>
#include <functional>
namespace NCL
{
	namespace CSC8503
	{
		class GameWorld;
	}
}

using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8599 {
		struct EVENT;
		struct EVENT_DEFINE {
			std::string name;
			bool delay = false;
			std::list<std::function<void(EVENT*)>> listFunc;
		};
		struct EVENT {
			EVENT_DEFINE* pEventDef;
			std::vector<std::string> vArg;
			bool operator == (const EVENT& other)
			{
				if (other.pEventDef != pEventDef) return false;
				if (other.vArg.size() != vArg.size()) return false;
				for (size_t i = 0; i < vArg.size(); i++)
				{
					if (vArg[i] != other.vArg[i]) return false;
				}
				return true;
			}
		};
		using EventDefContainer = std::map<std::string, EVENT_DEFINE*>;
		using EventDefContainerIterator = EventDefContainer::iterator;
		using EventQueueIterator = std::list<EVENT*>::iterator;
		class EventSystem :public AbstractStateMachine
		{
		public:
			void Update(float dt) override;
			std::string Print(int index) override;
			void GetActiveComponentArr(std::vector<std::string>& arr) override{}
			void RegisterEventHandler(const std::string&, const std::function<void(EVENT*)>&);
			void PushEvent(const std::string&, int n, ...);
			static EventSystem* getInstance() {
				if(instance==nullptr)
				{
					instance = new EventSystem();
				}
				return instance;
			}
			EVENT* HasHappened(const std::string&);
			void Reset();
		private:
			static EventSystem* instance;
			EventSystem();
			void init();
			void processEvent(EVENT& event);
			EventDefContainer eventDefContainer;
			std::list<EVENT*> eventQueue;
			std::list<EVENT*> eventQueueDelay;
			std::vector<EVENT*> eventRecords;
			float time = 0.0f;
		};
	}
}
