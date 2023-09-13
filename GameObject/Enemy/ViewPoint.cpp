#include "ViewPoint.h"

void ViewPoint::Initalize(const WorldTransform& worldTransform)
{
	worldTransform_.Initialize();
	worldTransform_.parent_ = &worldTransform;
	//model_
	float Angle = 0.2f;
	SetAngle(Angle);

}

void ViewPoint::Update()
{

	worldTransform_.UpdateMatrix();
	ImGui::Begin("ViewPoint");
	ImGui::End();
	CheckCollisions();
}

void ViewPoint::Draw()
{
}

void ViewPoint::SetDirection(const Vector3& Direction)
{
	if (Direction.x) {
		return;
	}
}

void ViewPoint::OnCollision(const uint32_t& attribute)
{
	if (attribute == kCollitionAttributeWall) {
		if (GetWorldPosition().x - GetRadius() > ColliderPosition.x + ColliderRadius) {
			float Radius = GetWorldPosition().x - ColliderPosition.x + ColliderRadius;
			SetRadius(Radius);
		}
		
	}
	if (attribute == kCollitionAttributePlayer) {
		ImGui::Begin("ViewPoint");
		ImGui::Text("Player On Collision");
		ImGui::End();
	}
}

Vector3 ViewPoint::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void ViewPoint::CheckCollisions()
{
	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		// イテレータAからコライダーを取得
		Collider* colliderA = *itrA;
		CheckCollisionPair(colliderA);
	}
}

void ViewPoint::CheckCollisionPair(Collider* collider)
{
	Vector3 posA, posB;
	posA = GetWorldPosition();
	posB = collider->GetWorldPosition();
	ColliderPosition = collider->GetWorldPosition();
	float Length = (float)sqrt(
		(posB.x - posA.x) * (posB.x - posA.x) + 
		(posB.z - posA.z) * (posB.z - posA.z));
	//マスクされていたら早期リターン
	if ((GetcollitionAttribute() & collider->GetcollisionMask()) == 0 && (collider->GetcollitionAttribute() & GetcollisionMask()) == 0) {
		return;
	}

	if (Length > GetRadius() + collider->GetRadius()) {
		return;
	}
	Vector2 fan_dir = {cosf(GetAngle()),sinf(GetAngle())};
	Vector2 normal_fan_to_point = {
		posB.x - posA.x / Length,
		posB.z - posA.z / Length
	};
	//内積
	float dot = normal_fan_to_point.x * fan_dir.x + normal_fan_to_point.y * fan_dir.y;
	float fan_cos = cosf(GetAngle()/2.0f);
	if (fan_cos <= dot) {
		OnCollision(collider->GetcollitionAttribute());
		collider->OnCollision(GetcollitionAttribute());
	}
	else {
		return;
	}
}
