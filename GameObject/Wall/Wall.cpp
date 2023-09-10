#include "Wall.h"

void Wall::Initialize()
{
	model = Model::CreateModelFromObj("resources", "cube.obj");

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.translation_ = { 5.0f,0.0f,0.0f };


}

void Wall::Update()
{
	SetRadius(worldTransform_.scale_.x);
	worldTransform_.UpdateMatrix();
}

void Wall::Draw(const ViewProjection& viewProjection)
{
	//プレイヤーの描画
	model->Draw(worldTransform_, viewProjection);
}

Vector3 Wall::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Wall::OnCollision()
{

}