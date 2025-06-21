#include "GameWorld.h"
#include "GameObject.h"
#include "Constraint.h"
#include "CollisionDetection.h"
#include "../../Common/Camera.h"
#include <algorithm>

using namespace NCL;
using namespace NCL::CSC8503;
GameWorld* GameWorld::p_self=nullptr;
GameWorld::GameWorld()	{
	mainCamera = new Camera();

	shuffleConstraints	= false;
	shuffleObjects		= false;
	worldIDCounter		= 0;
	p_self = this;
}

GameWorld::~GameWorld()	{
}

void GameWorld::Clear() {
	gameObjects.clear();
	constraints.clear();
}

void GameWorld::ClearAndErase() {
	for (auto& i : gameObjects) {
		delete i;
	}
	for (auto& i : constraints) {
		delete i;
	}
	Clear();
}

void GameWorld::AddGameObject(GameObject* o) {
	gameObjects.emplace_back(o);
	o->SetWorldID(worldIDCounter++);
}

void GameWorld::RemoveGameObject(GameObject* o, bool andDelete) {
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), o), gameObjects.end());
	if (andDelete) {
		delete o;
		o = nullptr;
	}
}

void GameWorld::GetObjectIterators(
	GameObjectIterator& first,
	GameObjectIterator& last) const {

	first	= gameObjects.begin();
	last	= gameObjects.end();
}

void GameWorld::OperateOnContents(GameObjectFunc f) {
	for (GameObject* g : gameObjects) {
		f(g);
	}
}

void GameWorld::UpdateWorld(float dt) {
	if (shuffleObjects) {
		std::random_shuffle(gameObjects.begin(), gameObjects.end());
	}

	if (shuffleConstraints) {
		std::random_shuffle(constraints.begin(), constraints.end());
	}
	for(const auto i:gameObjects)
	{
		i->update(dt);
		i->UI_update(mainCamera->BuildViewMatrix(),mainCamera->BuildProjectionMatrix());
	}
}

bool GameWorld::Raycast(Ray& r, RayCollision& closestCollision, bool closestObject) const {
	//The simplest raycast just goes through each object and sees if there's a collision
	RayCollision collision;

	for (auto& i : gameObjects) {
		if (i->GetLayer() == r.GetLayer()) {
			if (!i->GetBoundingVolume()) { //objects might not be collideable etc...
				continue;
			}
			RayCollision thisCollision;
			if (CollisionDetection::RayIntersection(r, *i, thisCollision)) {

				if (!closestObject) {
					closestCollision = collision;
					closestCollision.node = i;
					return true;
				}
				else {
					if (thisCollision.rayDistance < collision.rayDistance) {
						thisCollision.node = i;
						collision = thisCollision;
					}
				}
			}
		}
	}
	if (collision.node) {
		closestCollision		= collision;
		closestCollision.node	= collision.node;
		return true;
	}
	return false;
}


/*
Constraint Tutorial Stuff
*/

void GameWorld::AddConstraint(Constraint* c) {
	constraints.emplace_back(c);
}

void GameWorld::RemoveConstraint(Constraint* c, bool andDelete) {
	constraints.erase(std::remove(constraints.begin(), constraints.end(), c), constraints.end());
	if (andDelete) {
		delete c;
	}
}

void GameWorld::GetConstraintIterators(
	std::vector<Constraint*>::const_iterator& first,
	std::vector<Constraint*>::const_iterator& last) const {
	first	= constraints.begin();
	last	= constraints.end();
}

GameObject* GameWorld::find_game_object(int id) 
{
	for (const auto i : gameObjects)
	{
		if (i->GetWorldID() == id)
			return i;
	}
	return nullptr;
}

GameObject* GameWorld::find_nearest_game_object(GameObject* origin) const
{                    
	float min_distance = (gameObjects[0]->GetTransform().GetPosition() -origin->GetTransform().GetPosition()).Length();
	GameObject* target = nullptr;
	for (const auto i : gameObjects)
	{
		const float temp = (i->GetTransform().GetPosition() - origin->GetTransform().GetPosition()).Length();
		if (i->GetWorldID()!=origin->GetWorldID()&&temp < min_distance)
		{
			min_distance = temp;
			target = i;
		}
	}
	return target;
}
