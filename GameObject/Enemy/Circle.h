#pragma once

#include "Model.h"
#include "Collider.h"
#include "CollisionConfig.h"

class Circle : public Collider
{
public:
	Circle();
	~Circle();
	//Base
	void Initalize(const WorldTransform& worldTransform);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	//Collider
	void OnCollision(const uint32_t& Attribute);
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* circleModel_ = nullptr;
	bool IsPlayerOnCollision = false;
};


