#include"Scenes/State/GameClearState.h"

void GameClearState::Initialize()
{
	textureManager_ = TextureManager::GetInstance();
	sprite = new Sprite();
	sprite->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	worldTransform_Sprite.Initialize();
	Texture = textureManager_->LoadTexture("resources/Clear.png");
}

void GameClearState::Update()
{
	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (!aButtonPressed)
			{
				StateNo = 1;

				aButtonPressed = true;

			}
		}
		else
		{
			aButtonPressed = false;
		}
	}
}

void GameClearState::Draw()
{
	sprite->Draw(worldTransform_Sprite, Texture);
}

