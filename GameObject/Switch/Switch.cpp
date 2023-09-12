#include "Switch.h"
#include <cassert>
#include "ImGuiManager.h"

void Switch::Initialize(Model* switchModel, Vector3 translation) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	model_ = switchModel;
}

void Switch::Update() {
	worldTransform_.UpdateMatrix();
}

void Switch::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Switch::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Switch::OnCollision(const uint32_t& Attribute) {
	if (Attribute == 0) {
		return;
	}
}