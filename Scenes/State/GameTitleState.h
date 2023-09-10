#pragma once
#include"IgameState.h"
#include "Input.h"

class GameTitleState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Input* input = nullptr;
	XINPUT_STATE joyState;
	bool aButtonPressed = false;
};
