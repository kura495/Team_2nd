#pragma once
#include "IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Light.h"
#include "Sphere.h"
#include "TextureManager.h"
#include "Model.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include "GameObject/Camera/Camera.h"
#include "GameObject/Camera/GameCamera.h"
#include "GameObject/Player/Player.h"
#include "GameObject/Enemy/Enemy.h"
#include "GameObject/Wall/Wall.h"
#include "GameObject/Ground/Ground.h"
#include "GameObject/Switch/Switch.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Math_Structs.h"
#include "Utility/CollisionManager.h"
#include "Utility/CollisionConfig.h"

class GamePlayState :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();

	void EnemySpawn(const Vector3& position);
	void WallSpawn(const Vector3& position);

private:
	//基本機能ズ
	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	GameCamera* gameCamera_ = nullptr;
	TextureManager* textureManager_ = nullptr;	
	Input* input = nullptr;
	Audio* audio = nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	GlobalVariables* globalVariables = nullptr;
	Model* model = nullptr;
	Model* groundModel = nullptr;
	Model* enemyModel;
	Model* bombModel_;
	Model* explosionModel_;
	Model* wallModel_;
	Model* switchModel_;
	//
	WorldTransform worldTransform_;
	WorldTransform worldTransform_Sprite;
	ViewProjection viewProjection_;

	//
	CollisionManager* collisionManager_;

	XINPUT_STATE JoyState;
	//3Dオブジェクトたち
	Player* player = nullptr;
	std::list<Enemy*> enemys_;
	Enemy* enemy_;
	Sphere* sphere;
	std::list<Wall*>walls_;
	Wall* wall_ = nullptr;
	Ground* ground = nullptr;
	Switch* switch_ = nullptr;
	//2Dオブジェクトたち
	Sprite* sprite;
	//
	//テクスチャハンドルたち
	int Texture;
	//
	//サウンドハンドルたち
	uint32_t mokugyo;
	//
	int Pan = 0;
	float Volume = 0.0f;
	//Sprite用の位置
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,360.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 640.0f,360.0f,0.0f,1.0f }
	};
	//
	int enemyCount = 0;
	int enemyCountMax = 0;
	int clearTimer = 0;
	int gameoverTimer = 0;
};