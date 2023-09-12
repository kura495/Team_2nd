#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"

class Enemy : public Collider {
public:
	void Initialize(Model* enemyModel);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void SetPosition(const Vector3& position);

	void OnCollision(const uint32_t& Attribute) override;

	bool isDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* enemyModel_ = nullptr;

	bool isDead_ = false;
};