#include "Enemy.h"

void Enemy::Initialize(Model* enemyModel) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	enemyModel_ = enemyModel;
	SetcollisionAttribute(kCollitionAttributeEnemy);
	SetcollisionMask(~kCollitionAttributeEnemy );
}

void Enemy::Update() {
	/*ImGui::Begin("Enemy");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -20, 20);
	ImGui::End();*/

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

void Enemy::OnCollision(const uint32_t& Attribute) { 
	if (Attribute == kCollitionAttributeBomb) {
		isDead_ = true;
	}
	
}