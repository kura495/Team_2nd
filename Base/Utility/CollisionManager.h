#pragma once
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"
#include <list>

class CollisionManager {
public:
	void AddCollider(Collider* collider) { colliders_.push_back(collider); }
	void ClearCollider() { colliders_.clear(); }
	void CheckAllCollisions();

private:
	/// <summary>
	/// コライダー登録用
	/// </summary>
	std::list<Collider*> colliders_;
	
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
