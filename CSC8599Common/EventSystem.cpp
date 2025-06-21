#include "pch.h"
#include "EventSystem.h"
EventSystem* EventSystem::instance = nullptr;
extern EVENT_DEFINE g_Events[] =
{
	{"ThreatChanged"},
	{"on_hit"},
	{"player_over_threat",true},
	{"player_die"},
	{"pet_die"},
	{"pet_taunt",true},
	{"fix_DebugA"},
	{"fix_DebugB"},
	{"MonsterDie"},
	{"GameStart"},
	{"GameReset"},
	{"GameInit"},
	{"fix_DebugC"},


	{"summon_dragon"},
	{"arrival",true},
	{"dragon_die",true},


};
NCL::CSC8599::EventSystem::EventSystem()
{
	init();
}

void NCL::CSC8599::EventSystem::	Update(float dt)
{
	if (!(eventQueueDelay.empty()))
	{
		const float WORK_STEP = 10;
		time += dt;
		if (time >= WORK_STEP)
		{
			auto event = *(eventQueueDelay.begin());
			processEvent(*event);
			eventQueueDelay.erase(eventQueueDelay.begin());
			time = 0.0f;
		}
	}



	std::list<EVENT*>::iterator it;
	for (it = eventQueue.begin(); it != eventQueue.end(); it++)
	{
		auto event = *it;
		bool bMultiPushed = false;
		for (auto itPrev = eventQueue.begin(); itPrev != it; itPrev++)
		{
			if (*itPrev == *it)
			{
				bMultiPushed = true;
				break;
			}
		}

		if (bMultiPushed) continue;
		processEvent(*event);
	}
	eventQueue.clear();
}

std::string NCL::CSC8599::EventSystem::Print(int index)
{
	std::string buffer;
	buffer += "Event Records:\n";
	for (auto i : eventRecords) {
		buffer += "[" + i->pEventDef->name + "]";
		for (auto j : i->vArg)
		{
			buffer += "("+j + ")";
		}
		buffer += "\n";
	}
	return buffer;
}

void NCL::CSC8599::EventSystem::RegisterEventHandler(const std::string& name, const std::function<void(EVENT*)>& func)
{
	eventDefContainer[name]->listFunc.emplace_back(func);
}

void NCL::CSC8599::EventSystem::PushEvent(const std::string& name, int n, ...)
{
	EVENT* event = new EVENT;
	event->pEventDef = eventDefContainer[name];
	va_list args;
	va_start(args, n);
	for (int i = 0; i < n; ++i) {
		event->vArg.emplace_back(va_arg(args, char*));
	}
	va_end(args);
	if (event->pEventDef->delay)
		eventQueueDelay.emplace_back(event);
	else
		eventQueue.emplace_back(event);
	eventRecords.emplace_back(event);
}

EVENT* NCL::CSC8599::EventSystem::HasHappened(const std::string& name)
{
	for (auto event : eventQueue) {
		if (event->pEventDef->name == name)
			return event;
	}
	for (auto event : eventQueueDelay) {
		if (event->pEventDef->name == name)
			return event;
	}
	return nullptr;
}

void EventSystem::Reset()
{
	eventQueue.clear();
	eventQueueDelay.clear();
	for(auto i:eventDefContainer)
	{
		i.second->listFunc.clear();
	}
	init();
}

void NCL::CSC8599::EventSystem::init()
{
	int nEventNum = sizeof(g_Events) / sizeof(EVENT_DEFINE);

	for (int i = 0; i < nEventNum; i++)
	{
		eventDefContainer[g_Events[i].name] = &(g_Events[i]);
	}
}

void NCL::CSC8599::EventSystem::processEvent(EVENT& event)
{
	EVENT_DEFINE* pEventDef = event.pEventDef;
	if (!pEventDef) return;


	if (!(pEventDef->listFunc.empty()))
	{
		for (auto func = event.pEventDef->listFunc.begin(); func != event.pEventDef->listFunc.end(); func++)
		{
			(*func)(&event);
		}
	}
}

