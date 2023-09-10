#include"Scenes/State/GameSelectState.h"

void GameSelectState::Initialize()
{

}

void GameSelectState::Update()
{
	ImGui::Begin("Info");
	ImGui::SliderInt("SelectStageNo", &selectStageNo, 1, 3);
	ImGui::Text("StageDecision : A Button");
	ImGui::Text("NextStage : B Button");
	ImGui::Text("ReturnStage : X Button");
	ImGui::End();

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {
			Vector3 move = {
					(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
					(float)joyState.Gamepad.sThumbLY / SHRT_MAX };

			if (Length(move) > threshold)
			{
				stickTimer--;
				if (stickTimer <= 0) {
					if (selectStageNo > 2) {
						selectStageNo = 1;
						stickTimer = 10;
					}
					else {
						selectStageNo += 1;
						stickTimer = 10;
					}
				}
			}
		}
		else {
			stickTimer = 10;
		}

		//NextStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (!bButtonPressed)
			{
				if (selectStageNo > 2) {
					selectStageNo = 1;
				}
				else {
					selectStageNo += 1;
				}

				bButtonPressed = true;
			}
		}
		else
		{
			bButtonPressed = false;
		}

		//ReturnStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			if (!xButtonPressed)
			{
				if (selectStageNo < 2) {
					selectStageNo = 3;
				}
				else {
					selectStageNo -= 1;
				}

				xButtonPressed = true;

			}
		}
		else
		{
			xButtonPressed = false;
		}

		//DecisionStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (!aButtonPressed)
			{
				StateNo = selectStageNo + 1;

				aButtonPressed = true;

			}
		}
		else
		{
			aButtonPressed = false;
		}

	}
}

void GameSelectState::Draw()
{

}
