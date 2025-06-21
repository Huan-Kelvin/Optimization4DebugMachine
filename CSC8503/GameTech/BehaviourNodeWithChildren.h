#pragma once
#include "BehaviourNode.h"
#include <vector>
//有一些节点可能有许多子节点
class BehaviourNodeWithChildren:public BehaviourNode
{
public:
	BehaviourNodeWithChildren(const std::string& nodeName) 
		:BehaviourNode(nodeName) {};//后面是初始化列表 对父类进行初始化
	~BehaviourNodeWithChildren() {
		for (auto& i : childNodes) {
			delete i;
		}
	}
	void AddChild(BehaviourNode* n) {
		childNodes.emplace_back(n);//  C++ 11 新增加的 emplace_back push_back会先创建这个元素再把它拷贝到容器中 emplace省去了创建和移动的过程
	}
	void Reset() override {
		currentState = Initialise;
		for (auto& i : childNodes) {
			i->Reset();
		}
		
	}
protected:
	std::vector<BehaviourNode*> childNodes;
};

