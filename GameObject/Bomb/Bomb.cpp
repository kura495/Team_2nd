#include "Bomb.h"
#include <cassert>
#include "ImGuiManager.h"

void Bomb::Initialize() {
	bombModel_.reset(Model::CreateModelFromObj("resources", "Bomb.obj"));
	explosionModel_.reset(Model::CreateModelFromObj("resources", "Bomb.obj"));

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	worldTransformExplosion_.Initialize();
	worldTransformExplosion_.scale_ = { 0.1f, 0.1f, 0.1f };
	worldTransform_.UpdateMatrix();
	worldTransformExplosion_.UpdateMatrix();
}

void Bomb::Update() {
	if (explosionTimer <= 120) {
		worldTransformExplosion_.scale_.x += 0.2f;
		worldTransformExplosion_.scale_.y += 0.2f;
		worldTransformExplosion_.scale_.z += 0.2f;
	}
	else {
		explosionTimer = 0;
		worldTransformExplosion_.scale_ = { 0.1f, 0.1f, 0.1f };
		isExplosionBomb = false;
	}

	if (isExplosionBomb == true) {
		explosionTimer++;

		ImGui::Begin("Bomb");
		ImGui::SliderFloat3("ExplosionScale", &worldTransformExplosion_.scale_.x, -360.0f, 360.0f);
		ImGui::SliderInt("ExplosionTimer", &explosionTimer, 0, 160);
		ImGui::End();
	}

	worldTransform_.UpdateMatrix();
	worldTransformExplosion_.UpdateMatrix();
}

void Bomb::Draw(const ViewProjection& viewProjection) {
	if (isSetBomb == true) {
		bombModel_->Draw(worldTransform_, viewProjection);
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
	isExplosionBomb = true;
	worldTransformExplosion_.scale_ = { 0.1f, 0.1f, 0.1f };
}