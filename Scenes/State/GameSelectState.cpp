#include"Scenes/State/GameSelectState.h"

void GameSelectState::Initialize()
{

}

void GameSelectState::Update()
{
	ImGui::Begin("Info");
	ImGui::SliderInt("SelectStageNo", &selectStageNo, 1, 3);
	ImGui::Text("StageSelect : LeftJoyStick");
	ImGui::Text("ReturnStage : X Button");
	ImGui::Text("%d", stickTimer);
	ImGui::End();

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.sThumbLX != 0 || joyState.Gamepad.sThumbLY != 0) {

			//StageSelect
			if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX > threshold)
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
			else {
				stickTimer--;
				if (stickTimer <= 0) {
					if (selectStageNo < 2) {
						selectStageNo = 3;
						stickTimer = 10;
					}
					else {
						selectStageNo -= 1;
						stickTimer = 10;
					}
				}
			}
		}
		else {
			stickTimer = 5;
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
