#pragma once
#include"IgameState.h"
#include "Input.h"
#include "VectorCalc.h"

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

	bool xButtonPressed = false;
	bool bButtonPressed = false;
	bool aButtonPressed = true;

	const float threshold = 0.7f;
	int stickTimer = 10;
};
