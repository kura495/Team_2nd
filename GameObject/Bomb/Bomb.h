#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Bomb {
public:
	void Initialize();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetBomb(WorldTransform playerPos);

	void ExplosionBomb();

private:
	WorldTransform worldTransform_;
	WorldTransform worldTransformExplosion_;

	std::unique_ptr<Model> bombModel_ = nullptr;
	std::unique_ptr<Model> explosionModel_ = nullptr;

	bool isSetBomb = false;
	bool isExplosionBomb = false;

	int explosionTimer = 0;
};
