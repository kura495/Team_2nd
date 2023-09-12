#include "Player.h"

void Player::Initialize(Model* explotionModel, Model* bombModel)
{
	input = Input::GetInstance();

	explotionModel_ = explotionModel;
	bombModel_ = bombModel;


	model = Model::CreateModelFromObj("resources", "Player.obj");

	worldTransform_.Initialize();

	const char* groupName = "Player";

	//GlobalVariables::GetInstance()->CreateGroup(groupName);
	GlobalVariables::GetInstance()->AddItem(groupName, "speed", speed);

	BombNum_ = 0;

	SetcollisionAttribute(kCollitionAttributePlayer);
	SetcollisionMask(~kCollitionAttributePlayer & ~kCollitionAttributeBomb);
}

void Player::Update()
{
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {

			if (isTouchObject == false)
			{
				// 速さ
				const float moveSpeed = 0.3f;

				// 移動量
				move = {
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


			}

			else if (isTouchObject == true)
			{
				collisionDirection = CollisionDirection();

				if (collisionDirection.x >= 0)
				{
					//移動量
					worldTransform_.translation_.x -= 0.1f;
					isTouchObject = false;
				}
				else
				{
					//移動量
					worldTransform_.translation_.x += 0.1f;
					isTouchObject = false;
				}

				if (collisionDirection.z >= 0)
				{
					//移動量
					worldTransform_.translation_.z -= 0.1f;
					isTouchObject = false;
				}
				else
				{
					//移動量
					worldTransform_.translation_.z += 0.1f;
					isTouchObject = false;
				}

			}

			//else if (isTouchObject == true)
			//{
			//	collisionDirection = { 0,0,0 };
			//	collisionDirection = CollisionDirection();

			//	//x:プラス && z:プラス
			//	if (GetWorldPosition().x > 0)
			//	{
			//		if (GetWorldPosition().z > 0)// z座標が中心より大さい場合&&x座標が中心より大きい場合
			//		{
			//			if (collisionDirection.x <= 0 )
			//			{
			//				// 左下から当たっている場合
			//				worldTransform_.translation_.x -= 0.1f;
			//				isTouchObject = false;
			//			}
			//			else
			//			{
			//				// 右上から当たっている場合
			//				worldTransform_.translation_.x += 0.1f;
			//				isTouchObject = false;
			//			}

			//			if (collisionDirection.z <= 0)
			//			{

			//				worldTransform_.translation_.z -= 0.1f;
			//				isTouchObject = false;
			//			}
			//			else
			//			{
			//				worldTransform_.translation_.z += 0.1f;
			//				isTouchObject = false;
			//			}

			//		}
			//		else //x:プラス && z:マイナス
			//		{
			//			
			//			if (collisionDirection.x <= 0 && collisionDirection.z <= 0) {
			//				// 左下から当たっている場合
			//				worldTransform_.translation_.x += 0.1f;
			//				worldTransform_.translation_.z += 0.1f;
			//				isTouchObject = false;
			//			}
			//			else {
			//				// 右上から当たっている場合
			//				worldTransform_.translation_.x += 0.1f;
			//				worldTransform_.translation_.z += 0.1f;
			//				isTouchObject = false;
			//			}
			//		}
			//	}
			//	else
			//	{
			//		if (GetWorldPosition().z > 0)// z座標が中心より小さい場合&&x座標が中心より小さい場合
			//		{
			//			//x:マイナス　z:プラス
			//			if (collisionDirection.x <= 0 )
			//			{
			//				//  右下から当たっている場合
			//				worldTransform_.translation_.x += 0.1f;
			//				isTouchObject = false;
			//			}
			//			else
			//			{
			//				// 左上から当たっている場合
			//				worldTransform_.translation_.x -= 0.1f;
			//				isTouchObject = false;
			//			}
			//			if (collisionDirection.z <= 0)
			//			{
			//				worldTransform_.translation_.z += 0.1f;
			//				isTouchObject = false;
			//			}
			//			else
			//			{
			//				worldTransform_.translation_.z -= 0.1f;
			//				isTouchObject = false;
			//			}
			//		}
			//		else
			//		{
			//			//x:マイナス　z:マイナス
			//			if (collisionDirection.x <= 0 ){
			//				// 右から当たっている場合
			//				worldTransform_.translation_.x += 0.1f;
			//				isTouchObject = false;
			//			}
			//			else {
			//				// 左から当たっている場合
			//				worldTransform_.translation_.x -= 0.1f;
			//				isTouchObject = false;
			//			}
			//			if (collisionDirection.z <= 0)
			//			{
			//				
			//				worldTransform_.translation_.z += 0.1f;
			//				isTouchObject = false;
			//			}
			//			else {
			//				// 上から当たっている場合
			//				worldTransform_.translation_.z -= 0.1f;
			//				isTouchObject = false;
			//			}

			//		}
			//	}


			//	isTouchObject = false;
			//}


			//// Y軸周り角度(θy)	歩いている方向に顔を向ける
			//worldTransform_.rotation_.y = LerpShortAngle(worldTransform_.rotation_.y, angle_, 0.1f);



		}
	}

	//爆弾
	Attack();

	//爆弾の更新
	bombs_.remove_if([](Bomb* bomb) {
		if (bomb->GetTimer() >= 60) {
			delete bomb;
			return true;
		}
		return false;
		});
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

void Player::Reset()
{
	BombNum_ = 0;

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
	}
	else {
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
	ImGui::SliderFloat("direction", &collisionDirection.x, -10, 10);
	ImGui::Text("isTouchObject : %d", &isTouchObject);
	ImGui::SliderFloat3("direction", &direction.x, -1, 1);

	ImGui::End();
}



void Player::Attack()
{

	//コントローラー操作
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
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
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (Switch::GetIsCollision() == true) {
				for (Bomb* bomb : bombs_)
				{
					bomb->ExplosionBomb();
				}
			}
		}
	}


}

Vector3 Player::CollisionDirection()
{

	for (Wall* wall : walls_) {
		direction.x = wall->GetWorldPosition().x - GetWorldPosition().x;
		direction.y = wall->GetWorldPosition().y - GetWorldPosition().y;
		direction.z = wall->GetWorldPosition().z - GetWorldPosition().z;


		// x軸方向の修正
		if (direction.x > 0) {
			direction.x = 1.0f;
		}
		else {
			direction.x = -1.0f;
		}

		// y軸方向の修正
		if (direction.y > 0) {
			direction.y = 1.0f;
		}
		else {
			direction.y = -1.0f;
		}

		// z軸方向の修正
		if (direction.z > 0) {
			direction.z = 1.0f;
		}
		else {
			direction.z = -1.0f;
		}



		float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		if (magnitude != 0) {
			direction.x /= magnitude;
			direction.y /= magnitude;
			direction.z /= magnitude;
		}


	}


	return direction;

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

