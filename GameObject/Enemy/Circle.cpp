#include "Circle.h"

Circle::Circle()
{
}
Circle::~Circle()
{
}

void Circle::Initalize(const WorldTransform& worldTransform)
{
	circleModel_ = new Model();
	circleModel_->CreateModelFromObj("resources", "Circle.obj");
	worldTransform_.Initialize();
	worldTransform_ = worldTransform;
	worldTransform_.translation_.y = 0.5f;
	worldTransform_.parent_ = &worldTransform;
	float Radius = 2.0f;
	SetRadius(Radius);
	SetcollisionAttribute(kCollitionAttributeEnemy);
	SetcollisionMask(~kCollitionAttributeEnemy&~kCollitionAttributeWall&~kCollitionAttributeBomb& kCollitionAttributeSwitch&~kCollitionAttributeBombExplode);
}

void Circle::Update()
{
	worldTransform_.UpdateMatrix();
}

void Circle::Draw(const ViewProjection& viewProjection)
{
	if (viewProjection.fovAngleY) {
		return;
	}
	//circleModel_->Draw(worldTransform_, viewProjection);
}

void Circle::OnCollision(const uint32_t& Attribute)
{
	if (Attribute == kCollitionAttributePlayer) {
		IsPlayerOnCollision = true;
	}
}

Vector3 Circle::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
