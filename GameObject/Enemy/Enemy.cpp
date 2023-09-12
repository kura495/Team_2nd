#include "Enemy.h"

void Enemy::Initialize() {
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };

	enemyModel_.reset(Model::CreateModelFromObj("resources", "axis.obj"));

	float Radius = 1.0f;
	SetRadius(Radius);
	SetcollisionAttribute(kCollisionAttributeEnemy);
	SetcollisionMask(~kCollisionAttributeEnemy);
}

void Enemy::Update() {
	worldTransform_.rotation_.y += 0.2f;
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if(isDead_ == false){
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

void Enemy::OnCollision(const uint32_t& collisionAttribute) {
	if (collisionAttribute == kCollisionAttributeBomb) {
		isDead_ = true;
	}
	else {
		return;
	}
	
}