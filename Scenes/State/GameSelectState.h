#pragma once
#include"IgameState.h"
#include "Input.h"

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
};
