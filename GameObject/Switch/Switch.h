#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"
#include "Input.h"
#include "GameObject/Player/Player.h"
#include <future>

class Switch : public Collider {
public:
	void Initialize(Model* switchModel,Vector3 translation);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void OnCollision(const uint32_t& Attribute) override;

	static bool GetIsCollision() { return IsCollision; }

private:
	WorldTransform worldTransform_;

	Model* model_;

	Input* input = nullptr;
	XINPUT_STATE joyState;

	static bool IsCollision;
	int collisionTimer = 0;
};
