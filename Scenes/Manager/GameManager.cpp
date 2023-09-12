#include"GameManager.h"
void GameManager::Run()
{
	Initialize();
	Gameloop();
	Release();
}
void GameManager::Initialize()
{
	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);
	//Engine
	myEngine = MyEngine::GetInstance();
	myEngine->Initialize();
	//Window
	winApp = WinApp::GetInstance();
	//DirectX
	directX = DirectXCommon::GetInstance();
	//Audio
	audio = Audio::GetInstance();
	audio->Initialize();
	//Input
	input = Input::GetInstance();
	input->Initialize(winApp);
	//ImGui
	imGuiManager = ImGuiManager::GetInstance();
	imGuiManager->Initialize(winApp, directX);
	//TextureManager
	textureManager = TextureManager::GetInstance();
	//Light
	light = Light::GetInstance();
	light->Initialize();
	//グローバル変数読み込み
	GlobalVariables::GetInstance()->LoadFiles();
	//State
	state[TITLE] = std::make_unique<GameTitleState>();
	state[SELECT] = std::make_unique<GameSelectState>();
	state[PLAY_STAGE1] = std::make_unique<GamePlayState>();
	state[PLAY_STAGE2] = std::make_unique<GamePlayState2>();
	state[PLAY_STAGE3] = std::make_unique<GamePlayState3>();
	state[CLEAR] = std::make_unique<GameClearState>();
	state[GAMEOVER] = std::make_unique<GameOverState>();
	for (int i = 0; i < GameStateMax; i++) {
		state[i]->Initialize();
	}
	GameState::StateNo = TITLE;
}
void GameManager::Gameloop()
{
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			imGuiManager->BeginFrame();
			directX->PreView();
			input->Update();
			state[GameState::StateNo]->Update();
			state[GameState::StateNo]->Draw();
			imGuiManager->EndFrame();
			directX->PostView();
		}
	}
	
}

void GameManager::Release()
{
	directX->Release();

	ImGui_ImplDX12_Shutdown();
	CoUninitialize();
}
