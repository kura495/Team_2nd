#include"Scenes/State/GameOverState.h"

void GameOverState::Initialize()
{
	textureManager_ = TextureManager::GetInstance();
	sprite = new Sprite();
	sprite->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	worldTransform_Sprite.Initialize();
	Texture = textureManager_->LoadTexture("resources/GameOver.png");
}

void GameOverState::Update()
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

void GameOverState::Draw()
{
	sprite->Draw(worldTransform_Sprite, Texture);
}

