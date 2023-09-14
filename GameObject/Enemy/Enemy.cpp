#include "Enemy.h"

void Enemy::Initialize(Model* enemyModel,int moveMode, Vector3 moveSpeed) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	enemyModel_ = enemyModel;
	moveMode_ = moveMode;
	moveSpeed_ = moveSpeed;
	SetcollisionAttribute(kCollitionAttributeEnemy);
	SetcollisionMask(~kCollitionAttributeEnemy & ~kCollitionAttributeBomb);
	circle = new Circle();
	circle->Initalize(worldTransform_);
	float Radius = 1.0f;
	SetRadius(Radius);
}

void Enemy::Update() {
	/*ImGui::Begin("Enemy");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -20, 20);
	ImGui::End();*/

	moveTimer++;

	if (moveTimer <= 90) {
		if (moveMode_ == 1) {
			worldTransform_.translation_.x += moveSpeed_.x;
		}
		if (moveMode_ == 2) {
			worldTransform_.translation_.z += moveSpeed_.z;
		}
		if (moveMode_ == 3) {
			worldTransform_.translation_.x += moveSpeed_.x;
			worldTransform_.translation_.z += moveSpeed_.z;
		}
	}
	if (moveTimer >= 90) {
		if (moveMode_ == 1) {
			worldTransform_.translation_.x -= moveSpeed_.x;
		}
		if (moveMode_ == 2) {
			worldTransform_.translation_.z -= moveSpeed_.z;
		}
		if (moveMode_ == 3) {
			worldTransform_.translation_.x -= moveSpeed_.x;
			worldTransform_.translation_.z -= moveSpeed_.z;
		}
	}
	if (moveTimer >= 180) {
		moveTimer = 0;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if(isDead_ == false){
		enemyModel_->Draw(worldTransform_, viewProjection);
		circle->Draw(viewProjection);
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
	if (Attribute == kCollitionAttributeBombExplode) {
		isDead_ = true;
	}
	
}