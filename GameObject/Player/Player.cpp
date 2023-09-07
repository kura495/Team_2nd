#include "Player.h"

void Player::Initialize()
{
	input = Input::GetInstance();
	model = Model::CreateModelFromObj("resources","bunny.obj");
	
	worldTransform_.Initialize();


	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName,"speed",speed);
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
			move.x = Normalize(move).x * moveSpeed;
			move.y = Normalize(move).y * moveSpeed;
			move.z = Normalize(move).z * moveSpeed;
			worldTransform_.translation_.x = worldTransform_.translation_.x + move.x;
			worldTransform_.translation_.y = worldTransform_.translation_.y + move.y;
			worldTransform_.translation_.z = worldTransform_.translation_.z + move.z;
		}
	}
	if (input->IspushKey(DIK_W)) {
		worldTransform_.translation_.y += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_S)) {
		worldTransform_.translation_.y -= 0.5f * speed;
	}
	if (input->IspushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.5f * speed;
	}
	else if (input->IspushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.5f * speed;
	}
	if (input->IspushKey(DIK_Q)) {
		worldTransform_.translation_.z += 0.5f * speed;
	}
	else if (input->IspushKey(DIK_E)) {
		worldTransform_.translation_.z -= 0.5f * speed;
	}
	if (input->IspushKey(DIK_1)) {
		worldTransform_.scale_.x -= 0.5f * speed;
		worldTransform_.scale_.y -= 0.5f * speed;
		worldTransform_.scale_.z -= 0.5f * speed;
	}
	else if (input->IspushKey(DIK_2)) {
		worldTransform_.scale_.x += 0.5f * speed;
		worldTransform_.scale_.y += 0.5f * speed;
		worldTransform_.scale_.z += 0.5f * speed;
	}
	
	ImGui();
	worldTransform_.UpdateMatrix();
	ApplyGlobalVariables();
}

void Player::Draw(const ViewProjection& viewProjection)
{
	model->Draw(worldTransform_, viewProjection);
}

void Player::ApplyGlobalVariables()
{
	const char* groupName = "Player";
	speed = GlobalVariables::GetInstance()->GetfloatValue(groupName, "speed");
}

void Player::ImGui()
{
	ImGui::Begin("Player");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x,-10, 10);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x,-10, 10);
	ImGui::SliderFloat3("scale", &worldTransform_.scale_.x,-10, 10);
	ImGui::End();
}
