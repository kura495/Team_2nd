#pragma once
#include"IgameState.h"
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"

class GameClearState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();
private:
	Input* input = nullptr;
	XINPUT_STATE joyState;
	bool aButtonPressed = false;

	TextureManager* textureManager_ = nullptr;

	//Sprite
	Sprite* sprite;
	int Texture;
	WorldTransform worldTransform_Sprite;
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,720.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 1280.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 1280.0f,720.0f,0.0f,1.0f }
	};
};
