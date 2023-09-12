﻿#include "Player.h"

void Player::Initialize()
{
	input = Input::GetInstance();
	model = Model::CreateModelFromObj("resources", "bunny.obj");

	worldTransform_.Initialize();


	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName, "speed", speed);

	float Radius = 1;
	SetRadius(Radius);
}

void Player::Update()
{
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {
			// 速さ
			const float moveSpeed = 0.3f;
			// 移動量
			Vector3 move = {
				(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
				(float)joyState.Gamepad.sThumbLY / SHRT_MAX };

			if (Length(move) > threshold)
			{
				isMove = true;
			}

			if (isMove == true)
			{
				//反映
				move.x = Normalize(move).x * moveSpeed;
				move.y = Normalize(move).y * moveSpeed;
				move.z = Normalize(move).z * moveSpeed;

				//目標角度の算出
				angle_ = std::atan2(move.x, move.z);

			}
			//移動量
			worldTransform_.translation_.x = worldTransform_.translation_.x + move.x;
			worldTransform_.translation_.y = worldTransform_.translation_.y + move.y;
			worldTransform_.translation_.z = worldTransform_.translation_.z + move.z;

			//// Y軸周り角度(θy)	歩いている方向に顔を向ける
			//worldTransform_.rotation_.y = LerpShortAngle(worldTransform_.rotation_.y, angle_, 0.1f);



		}
	}

	if (input->IspushKey(DIK_W)) {
		worldTransform_.translation_.z += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_S)) {
		worldTransform_.translation_.z -= 0.5f * speed;
	}
	if (input->IspushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.5f * speed;
	}
	else if (input->IspushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.5f * speed;
	}
	//if (input->IspushKey(DIK_Q)) {
	//	worldTransform_.translation_.z += 0.5f * speed;
	//}
	//else if (input->IspushKey(DIK_E)) {
	//	worldTransform_.translation_.z -= 0.5f * speed;
	//}
	//if (input->IspushKey(DIK_1)) {
	//	worldTransform_.scale_.x -= 0.5f * speed;
	//	worldTransform_.scale_.y -= 0.5f * speed;
	//	worldTransform_.scale_.z -= 0.5f * speed;
	//}
	//else if (input->IspushKey(DIK_2)) {
	//	worldTransform_.scale_.x += 0.5f * speed;
	//	worldTransform_.scale_.y += 0.5f * speed;
	//	worldTransform_.scale_.z += 0.5f * speed;
	//}

	//爆弾
	Attack();

	//爆弾の更新
	for (Bomb* bomb : bombs_)
	{
		bomb->Update();
	}


	ImGui();
	worldTransform_.UpdateMatrix();
	ApplyGlobalVariables();
}

void Player::Draw(const ViewProjection& viewProjection)
{
	//プレイヤーの描画
	model->Draw(worldTransform_, viewProjection);

	//爆弾の描画
	for (Bomb* bomb : bombs_) {
		bomb->Draw(viewProjection);
	}

}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision(const uint32_t& collisionAttribute)
{
	ImGui::Begin("Player");
	if (collisionAttribute == kCollisionAttributeEnemy) {
		ImGui::Text("Player On Enemy");
	}
	else if (collisionAttribute == kCollisionAttributeBomb) {
		ImGui::Text("Player On Bomb");
	}
	ImGui::End();
}

void Player::ApplyGlobalVariables()
{
	const char* groupName = "Player";
	speed = GlobalVariables::GetInstance()->GetfloatValue(groupName, "speed");
}

void Player::ImGui()
{
	ImGui::Begin("Player");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -10, 10);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10, 10);
	ImGui::SliderFloat3("scale", &worldTransform_.scale_.x, -10, 10);
	ImGui::End();
}

void Player::Attack()
{

	//キーボード操作
	if (input->pushKey(DIK_SPACE))
	{
		//爆弾の生成と初期化
		newBomb = new Bomb();
		newBomb->Initialize();

		//爆弾の設置(プレイヤーと同じ位置に)
		newBomb->SetBomb(worldTransform_);

		//爆弾をリストに登録
		bombs_.push_back(newBomb);


	}

	//コントローラー操作
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{


		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			//爆弾の生成と初期化
			newBomb = new Bomb();
			newBomb->Initialize();

			//爆弾の設置(プレイヤーと同じ位置に)
			newBomb->SetBomb(worldTransform_);

			//爆弾をリストに登録
			bombs_.push_back(newBomb);

		}

		//爆発させる
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			for (Bomb* bomb : bombs_)
			{
				bomb->ExplosionBomb();
			}
		}
	}


}

float Player::Lerp(const float& a, const float& b, float t) {
	float result{};

	result = a + b * t;

	return result;
}

// 最短角度補間
float Player::LerpShortAngle(float a, float b, float t)
{
	// 角度差分を求める
	float diff = b - a;

	diff = std::fmod(diff, 2 * (float)std::numbers::pi);
	if (diff < 2 * (float)-std::numbers::pi)
	{
		diff += 2 * (float)std::numbers::pi;
	}
	else if (diff >= 2 * std::numbers::pi)
	{
		diff -= 2 * (float)std::numbers::pi;
	}

	diff = std::fmod(diff, 2 * (float)std::numbers::pi);
	if (diff < (float)-std::numbers::pi)
	{
		diff += 2 * (float)std::numbers::pi;
	}
	else if (diff >= (float)std::numbers::pi)
	{
		diff -= 2 * (float)std::numbers::pi;
	}

	return Lerp(a, diff, t);
}

