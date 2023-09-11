#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"
#include "Input.h"
#include "GameObject/Player/Player.h"

class Switch : public Collider {
public:
	void Initialize(Model* switchModel,Vector3 translation);

	void Update(Player* player);

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void OnCollision() override;

private:
	WorldTransform worldTransform_;

	Model* model_;

	Input* input = nullptr;
	XINPUT_STATE joyState;

	int timer = 59;
	bool timerOn = false;
};
