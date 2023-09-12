#pragma once
#include"IgameState.h"
#include "Input.h"
#include "VectorCalc.h"
#include "Sprite.h"
#include "TextureManager.h"

class GameSelectState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Input* input = nullptr;
	XINPUT_STATE joyState;
	
	int selectStageNo = 1;

	bool aButtonPressed = true;

	const float threshold = 0.7f;
	int stickTimer = 5;

	TextureManager* textureManager_ = nullptr;

	//Sprite
	Sprite* stage1;
	int stage1Tex;
	WorldTransform worldTransform_Stage1Sprite;
	Vector4 Stage1SpriteLeftTop[2] = {
		{ 400.0f,225.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 Stage1SpriteLeftBottom[2] = {
		{ 400.0f,495.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 Stage1SpriteRightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 800.0f,225.0f,0.0f,1.0f }
	};
	Vector4 Stage1SpriteRightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 800.0f,495.0f,0.0f,1.0f }
	};

	Sprite* stage2;
	int stage2Tex;
	WorldTransform worldTransform_Stage2Sprite;
	Vector4 Stage2SpriteLeftTop[2] = {
		{ 400.0f,225.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 Stage2SpriteLeftBottom[2] = {
		{ 400.0f,495.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 Stage2SpriteRightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 800.0f,225.0f,0.0f,1.0f }
	};
	Vector4 Stage2SpriteRightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 800.0f,495.0f,0.0f,1.0f }
	};

	Sprite* stage3;
	int stage3Tex;
	WorldTransform worldTransform_Stage3Sprite;
	Vector4 Stage3SpriteLeftTop[2] = {
		{ 400.0f,225.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 Stage3SpriteLeftBottom[2] = {
		{ 400.0f,495.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 Stage3SpriteRightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 800.0f,225.0f,0.0f,1.0f }
	};
	Vector4 Stage3SpriteRightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 800.0f,495.0f,0.0f,1.0f }
	};

	Sprite* sprite;
	int TextureS1;
	int TextureS2;
	int TextureS3;
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
