#include "Switch.h"
#include <cassert>
#include "ImGuiManager.h"

void Switch::Initialize(Model* switchModel, Vector3 translation) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	model_ = switchModel;
}

void Switch::Update(Player* player) {
	worldTransform_.UpdateMatrix();

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			timerOn = true;
		}
	}

	if (timerOn == true) {
		for (Bomb* pBomb : player->GetBombs()) {
			pBomb->ExplosionBomb();
			Sleep(1000 * 1);
		}
	}
	if (timer >= 60) {
	
		timer = 0;
	}

	/*std::list<Bomb*> pBomb;
	pBomb = player->GetBombs();

	std::list<Bomb*>::iterator itr = pBomb.begin();
	if (timerOn == true) {
		timer++;
	}
	if (timer >= 60) {
		*itr = 0;
		
		for (; itr != pBomb.end();) {
			Bomb* bomb = new Bomb;
			bomb = *itr;
			bomb->ExplosionBomb();
			itr++;
			break;
		}
		itr++;
		timer = 0;
	}*/

	ImGui::Begin("Switch");
	ImGui::Text("%d", timer);
	ImGui::End();

	/*if (timerOn == true) {
		for (Bomb* pBomb : player->GetBombs()) {
			for (int i = 0; i <= 60; i++) {
				if (i <= 60) {
					pBomb->ExplosionBomb();
				}
			}
		}
	}*/
}

void Switch::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Switch::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Switch::OnCollision() {}