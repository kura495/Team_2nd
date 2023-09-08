#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"

class Bomb : public Collider {
public:
	void Initialize();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetBomb(WorldTransform playerPos);

	void ExplosionBomb();

	Vector3 GetWorldPosition() override;

	void OnCollision() override;

private:
	WorldTransform worldTransform_;
	WorldTransform worldTransformExplosion_;

	std::unique_ptr<Model> bombModel_ = nullptr;
	std::unique_ptr<Model> explosionModel_ = nullptr;

	bool isSetBomb = false;
	bool isExplosionBomb = false;

	int explosionTimer = 0;
};
