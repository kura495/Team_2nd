#pragma once
#include "IgameState.h"
#include "Input.h"

class GamePlayState3 :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();

private:
	Input* input = nullptr;
};
