#include "Player.h"

void Player::Initialize(Model* explotionModel, Model* bombModel)
{
	input = Input::GetInstance();

	explotionModel_ = explotionModel;
	bombModel_ = bombModel;


	model = Model::CreateModelFromObj("resources", "Player.obj");

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 26, 0, -11 };
	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName, "speed", speed);

	BombNum_ = 0;

	SetcollisionAttribute(kCollitionAttributePlayer);
	SetcollisionMask(~kCollitionAttributePlayer & ~kCollitionAttributeBomb);
}

void Player::Update()
{
Input::GetInstance()->GetJoystickState(0,joyState);

	if (input->IspushKey(DIK_W)) {
		move.z = 10000.0f;
	}
	else if (input->IspushKey(DIK_S)) {
		move.z = -10000.0f;
	}
	else {
		move.z = 0;
	}
	if (input->IspushKey(DIK_A)) {
		move.x = -10000.0f;
	}
	else if (input->IspushKey(DIK_D)) {
		move.x = 10000.0f;
	}
	else {
		move.x = 0;
	}
	
	if (isTouchObject == false)
	{
		// 速さ
		const float moveSpeed = 0.3f;
		
		// 移動量
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {
			move = {
				(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
				(float)joyState.Gamepad.sThumbLY / SHRT_MAX };
		}
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

		savePosition = worldTransform_.translation_;

	}

	//LeftMoveLimit
	if (worldTransform_.translation_.x <= moveLimitX.x) {
		worldTransform_.translation_.x = moveLimitX.x + 0.1f;
	}
	//RightMoveLimit
	if (worldTransform_.translation_.x >= moveLimitX.y) {
		worldTransform_.translation_.x = moveLimitX.y - 0.1f;
	}
	//TopMoveLimit
	if (worldTransform_.translation_.z >= moveLimitY.x) {
		worldTransform_.translation_.z = moveLimitY.x - 0.1f;
	}
	//BottomMoveLimit
	if (worldTransform_.translation_.z <= moveLimitY.y) {
		worldTransform_.translation_.z = moveLimitY.y + 0.1f;
	}

	//爆弾
	Attack();

	//爆弾の更新
	bombs_.remove_if([](Bomb* bomb) {
		if (bomb->GetTimer() >= 40) {
			delete bomb;
			return true;
		}
		return false;
		});
	for (Bomb* bomb : bombs_)
	{
		bomb->Update();
	}
	worldTransform_.UpdateMatrix();
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

void Player::Reset()
{
	isDead = false;
	BombNum_ = 0;
	bombs_.clear();
	worldTransform_.translation_ = { 26, 0, -11 };
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision(const uint32_t& Attribute)
{
	if (Attribute == kCollitionAttributeWall) {
		isTouchObject = true;

		if (isTouchObject == true)
		{
			std::list<Wall*>::iterator itrA = walls_.begin();

			for (; itrA != walls_.end(); ++itrA)
			{
				Wall* wallA = *itrA;
				float distance = Length(Subtract(wallA->GetWorldPosition(), GetWorldPosition()));

				if (distance < wallA->GetRadius() + GetRadius())
				{
					//矩形の当たり判定
					if (wallA->GetWorldPosition().x - wallA->GetRadius() <= GetWorldPosition().x + GetRadius() && GetWorldPosition().x - GetRadius() <= wallA->GetWorldPosition().x + wallA->GetRadius())
					{
						if (wallA->GetWorldPosition().z - wallA->GetRadius() <= GetWorldPosition().z + GetRadius() && GetWorldPosition().z - GetRadius() <= wallA->GetWorldPosition().z + wallA->GetRadius())
						{
							
								//向き
								if (wallA->GetWorldPosition().x >= savePosition.x)
								{
									worldTransform_.translation_.x = savePosition.x - 0.3f;
									isTouchObject = false;
								}
								else if (wallA->GetWorldPosition().x < savePosition.x)
								{
									worldTransform_.translation_.x = savePosition.x + 0.3f;
									isTouchObject = false;
								}
							


								if (wallA->GetWorldPosition().z > savePosition.z)
								{
									worldTransform_.translation_.z = savePosition.z - 0.3f;
									isTouchObject = false;
								}
								else if (wallA->GetWorldPosition().z < savePosition.z)
								{
									worldTransform_.translation_.z = savePosition.z + 0.3f;
									isTouchObject = false;
								}
							

						}
					}


					break;
				}
			}
		}

	}
	else if(Attribute == kCollitionAttributeEnemy){
		isDead = true;
	}
	else {
		isDead = false;
		return;
	}

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
	ImGui::Text("isTouchObject : %d", &isTouchObject);

	ImGui::End();
}



void Player::Attack()
{

	//コントローラー操作
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X||input->IsTreggerKey(DIK_C))
		{
			if (!xButtonPressed)
			{
				//爆弾の生成と初期化
				if (BombNum_ < MaxBomb_)	//設置する個数は五個まで
				{
					newBomb = new Bomb();
					newBomb->Initialize(bombModel_, explotionModel_);

					//爆弾の設置(プレイヤーと同じ位置に)
					newBomb->SetBomb(worldTransform_);

					//爆弾をリストに登録
					bombs_.push_back(newBomb);

					BombNum_++;

					//長押しを受け付けない
					xButtonPressed = true;
				}
			}
		}
		else
		{
			//xボタンが押されていない場合、フラグをリセット
			xButtonPressed = false;
		}


		//爆発させる
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B || input->IsTreggerKey(DIK_SPACE))
		{
			if (Switch::GetIsCollision() == true) {
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

//減算
Vector3 Player::Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

