#pragma once
#include <string>
enum BehaviourState {
	Initialise,
	Failure,
	Success,
	Ongoing
};

class BehaviourNode
{//节点拥有一个名字和状态
public:
	BehaviourNode(const std::string& nodeName) {
		currentState = Initialise;
		name = nodeName;
	}
	virtual ~BehaviourNode() {}
	virtual BehaviourState Execute(float dt) = 0;//纯虚函数

	virtual void Reset() { currentState = Initialise;}
protected:
	BehaviourState currentState;
	std::string name;
};

