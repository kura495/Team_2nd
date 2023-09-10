#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"

class Wall : public Collider
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void OnCollision() override;

private:
	WorldTransform worldTransform_;


	Model* model = nullptr;
};

