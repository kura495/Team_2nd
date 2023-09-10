#include"Scenes/State/GameTitleState.h"

void GameTitleState::Initialize()
{

}

void GameTitleState::Update()
{
	ImGui::Begin("Info");
	ImGui::Text("NextScene : A Button");
	ImGui::End();
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			StateNo = 1;
		}
	}
}

void GameTitleState::Draw()
{

}
