#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"

class Bomb : public Collider {
public:
	void Initialize(Model* bombModel, Model* explosionModel);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetBomb(WorldTransform playerPos);

	void ExplosionBomb();

	Vector3 GetWorldPosition() override;

	void OnCollision() override;

	int GetTimer() { return explosionTimer; }

private:
	WorldTransform worldTransform_;
	WorldTransform worldTransformExplosion_;

	Model* bombModel_;
	Model* explosionModel_;

	bool isSetBomb = false;
	bool isExplosionBomb = false;

	int explosionTimer = 0;
};
