#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"
#include "Circle.h"

class Enemy : public Collider {
public:
	void Initialize(Model* enemyModel, int moveMode, Vector3 moveSpeed);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void SetPosition(const Vector3& position);

	void OnCollision(const uint32_t& Attribute) override;

	bool isDead() const { return isDead_; }

	void SetDead(bool isDead) { isDead_ = isDead; }

private:
	WorldTransform worldTransform_;
	Model* enemyModel_ = nullptr;
	Circle* circle = nullptr;
	bool isDead_ = false;

	int moveMode_ = 0;
	Vector3 moveSpeed_ = { 0.0f,0.0f,0.0f };
	int moveTimer = 0;
};