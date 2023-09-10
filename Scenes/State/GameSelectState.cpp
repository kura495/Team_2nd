#include"Scenes/State/GameSelectState.h"

void GameSelectState::Initialize()
{

}

void GameSelectState::Update()
{
	ImGui::Begin("Info");
	ImGui::SliderInt("SelectStageNo", &selectStageNo, 1, 3);
	ImGui::Text("StageDecision : Y Button");
	ImGui::Text("NextStage : B Button");
	ImGui::Text("ReturnStage : X Button");
	ImGui::End();

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		//NextStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (selectStageNo > 3) {
				selectStageNo = 1;
			}
			else {
				selectStageNo += 1;
			}
		}
		//ReturnStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			if (selectStageNo < 1) {
				selectStageNo = 3;
			}
			else {
				selectStageNo -= 1;
			}
		}
		//DecisionStage
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			StateNo = selectStageNo + 1;
		}
	}
}

void GameSelectState::Draw()
{

}
