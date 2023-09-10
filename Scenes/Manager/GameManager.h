#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Mesh.h"
#include"TextureManager.h"
#include"Light.h"
#include"ImGuiManager.h"
#include"Scenes/State/GameTitleState.h"
#include"Scenes/State/GameSelectState.h"
#include"Scenes/State/GamePlayState.h"
#include"Scenes/State/GamePlayState2.h"
#include"Scenes/State/GamePlayState3.h"
#include"Scenes/State/GameClearState.h"
#include"Scenes/State/IgameState.h"
#include"Audio.h"
#include"Input.h"
#include"GlobalVariables.h"

class GameManager
{
public:
	enum GameStateNo {
		TITLE,
		SELECT,
		PLAY_STAGE1,
		PLAY_STAGE2,
		PLAY_STAGE3,
		CLEAR,
		GameStateMax
	};

	void Run();
	
private:

	//Base
	MyEngine* myEngine = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	TextureManager* textureManager = nullptr;

	ImGuiManager* imGuiManager = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	
	Light* light = nullptr;

	MSG msg{};
	//State
	std::unique_ptr<GameState>state[GameStateMax];
	Vector4 ClearColor{ 0.1f,0.25f,0.5f,1.0f };
	
	void Initialize();
	void Gameloop();
	void Release();
};


