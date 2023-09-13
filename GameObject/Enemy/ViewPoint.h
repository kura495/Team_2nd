#pragma once
#include "Fancollider.h"

#include "WorldTransform.h"

#include "Model.h"

#include "CollisionConfig.h"

class ViewPoint : public FanCollider
{
public:
	//Base
	void Initalize(const WorldTransform& worldTransform);
	void Update();
	void Draw();
	//
	void SetDirection(const Vector3& Direction);
	//virtual Function FanCollider
	void OnCollision(const uint32_t& attribute)override;
	
	Vector3 GetWorldPosition();
	//CollisionCheck
	void CheckCollisions();
	void CheckCollisionPair(Collider* collider);
	void AddCollider(Collider* collider) { colliders_.push_back(collider); }
	void ClearCollider() { colliders_.clear(); }

private:
	/// <summary>
	/// コライダー登録用
	/// </summary>
	std::list<Collider*> colliders_;

	Vector3 ColliderPosition;
	float ColliderRadius;

	Model* model_ = nullptr;

	WorldTransform worldTransform_;

};

