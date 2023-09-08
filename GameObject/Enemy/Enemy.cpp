#include "Enemy.h"

void Enemy::Initialize() {
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };


	enemyModel_.reset(Model::CreateModelFromObj("resources", "axis.obj"));
}

void Enemy::Updata() {
	worldTransform_.rotation_.x += 0.2;
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if(isDead_ = false){
		enemyModel_->Draw(worldTransform_, viewProjection);
	}
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::SetPosition(const Vector3& position) {
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
}

void Enemy::OnCollision() { isDead_ = true; }