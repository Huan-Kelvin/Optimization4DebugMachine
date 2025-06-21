#pragma once
#include <ostream>
#include <stack>
#include <vector>

#include "StateMachine.h"
/*
 * 自适应系统
 *
 * 引入两个概念  环境和代理
 *
 * 环境： 代理运行的上下文 这里具体指的是怪兽 Debug状态机 龙 组成的环境
 *
 * 代理： 需要被观测的个体 这里指怪兽 龙的状态机（玩家在这个环境下暂时不需要被关注)
 */
namespace NCL {
	namespace CSC8599
	{
		class State;
		class StateMachine;
		using Path = std::stack<State*>;
		using Environment = std::pair<std::string,std::vector<StateMachine*>>;
		using EnvContainer = std::vector<Environment*>;
		class AdaptiveDebugSystem
		{
			friend std::ostream& operator<<(std::ostream& os, const AdaptiveDebugSystem& obj)
			{
				std::string buffer("AdaptiveDebugSystem:\n");
				for(const auto i: obj.env_container_)
				{
					buffer += i->first+":\n";
					for(const auto j:i->second)
					{
						buffer += j->Print(0)+"\n";
					}
				}
				return os << buffer;
			}

		public:
			static AdaptiveDebugSystem* getInstance()
			{
				if(instance==nullptr)
				{
					instance = new AdaptiveDebugSystem();
				}
				return instance;
			}
			void insert(Environment* env);
			void update(float dt);
		protected:
			EnvContainer env_container_;
		private:
			static AdaptiveDebugSystem* instance;
			AdaptiveDebugSystem();
			void adjust(Path path, StateMachine* state_machine);
			Environment* find_deadlock_env();
			Path re_plan(StateMachine* state_machine);
		};
	}
}


