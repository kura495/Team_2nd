#include "Bomb.h"
#include <cassert>
#include "ImGuiManager.h"

void Bomb::Initialize(Model* bombModel,Model* explosionModel) {
	bombModel_ = bombModel;
	explosionModel_ = explosionModel;

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTransformExplosion_.Initialize();
	worldTransformExplosion_.scale_ = { 0.0f, 0.0f, 0.0f };
	worldTransform_.UpdateMatrix();
	worldTransformExplosion_.UpdateMatrix();
	SetcollisionAttribute(kCollitionAttributeBomb);
	SetcollisionMask(~kCollitionAttributeBomb);
}

void Bomb::Update() {
	if (explosionTimer <= 40) {
		if (isExplosionBomb == true) {
			worldTransformExplosion_.scale_.x += 0.2f;
			worldTransformExplosion_.scale_.y += 0.2f;
			worldTransformExplosion_.scale_.z += 0.2f;
			worldTransformExplosion_.rotation_.y += 0.1f;
			SetRadius(worldTransformExplosion_.scale_.y);
		}
	}
	else {
		explosionTimer = 0;
		worldTransformExplosion_.scale_ = { 0.0f, 0.0f, 0.0f };
		isExplosionBomb = false;
		isSetBomb = false;
	}

	ImGui::Begin("bomb");
	ImGui::Text("timer");
	ImGui::End();

	if (isExplosionBomb == true) {
		explosionTimer++;
	}

	worldTransform_.UpdateMatrix();
	worldTransformExplosion_.UpdateMatrix();
}

void Bomb::Draw(const ViewProjection& viewProjection) {
	if (isSetBomb == true) {
		bombModel_->Draw(worldTransform_, viewProjection);
		explosionModel_->Draw(worldTransformExplosion_, viewProjection);
	}
	if (isExplosionBomb == true) {
		explosionModel_->Draw(worldTransformExplosion_, viewProjection);
	}
}

void Bomb::SetBomb(WorldTransform playerPos) {
	worldTransform_.translation_ = playerPos.translation_;
	worldTransformExplosion_.translation_ = playerPos.translation_;
	isSetBomb = true;
}

void Bomb::ExplosionBomb() {
	if (isSetBomb == true) {
		isExplosionBomb = true;
	}
}

Vector3 Bomb::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransformExplosion_.matWorld_.m[3][0];
	worldPos.y = worldTransformExplosion_.matWorld_.m[3][1];
	worldPos.z = worldTransformExplosion_.matWorld_.m[3][2];
	return worldPos;
}

void Bomb::OnCollision(const uint32_t& Attribute) {
	if (Attribute == 0) {
		return;
	}
}