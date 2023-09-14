#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	gameCamera_ = new GameCamera();
	gameCamera_->Initalize();

	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	DirectX_ = DirectXCommon::GetInstance();
	collisionManager_ = new CollisionManager();
	//
	//3Dオブジェクト生成



	model = Model::CreateModelFromObj("resources", "bunny.obj");
	bombModel_ = Model::CreateModelFromObj("resources", "Bomb.obj");
	explosionModel_ = Model::CreateModelFromObj("resources", "ExplosionBomb.obj");
	enemyModel = Model::CreateModelFromObj("resources", "enemy.obj");
	wallModel_ = Model::CreateModelFromObj("resources", "cube.obj");
	groundModel = Model::CreateModelFromObj("resources", "ground.obj");
	switchModel_ = Model::CreateModelFromObj("resources", "Switch.obj");


	WallSpawn(Vector3(8, 0, 5));


	player = new Player();
	player->Initialize(explosionModel_, bombModel_);
	for (Wall* wall : walls_) {
		player->SetWall(wall);
	}
	sphere = new Sphere();
	sphere->Initialize();
	ground = new Ground();
	ground->Initialize(groundModel);
	switch_ = new Switch();
	switch_->Initialize(switchModel_, Vector3(26, 0, -12));

	EnemySpawn(Vector3(8, -1, 2),0,Vector3{0.0f,0.0f,0.0f});

	EnemySpawn(Vector3(-10, -1, 0), 0, Vector3{ 0.0f,0.0f,0.0f });

	EnemySpawn(Vector3(-12, -1, 16), 0, Vector3{ 0.0f,0.0f,0.0f });

	enemyCountMax = enemyCount;


	//
	//2Dオブジェクト作成
	

	enemySay = new Sprite();
	enemySay->Initialize(EnemySpriteLeftTop[0], EnemySpriteLeftBottom[0], EnemySpriteRightTop[1], EnemySpriteRightBottom[1]);
	worldTransform_EnemySprite.Initialize();
	enemySayTexture = textureManager_->LoadTexture("resources/enemySay.png");

	playerSay = new Sprite();
	playerSay->Initialize(Stage2SpriteLeftTop[0], Stage2SpriteLeftBottom[0], Stage2SpriteRightTop[1], Stage2SpriteRightBottom[1]);
	worldTransform_PlayerSprite.Initialize();
	playerSayTexture = textureManager_->LoadTexture("resources/playerSay.png");

	switchSay = new Sprite();
	switchSay->Initialize(Stage3SpriteLeftTop[0], Stage3SpriteLeftBottom[0], Stage3SpriteRightTop[1], Stage3SpriteRightBottom[1]);
	worldTransform_Stage3Sprite.Initialize();
	switchTexture = textureManager_->LoadTexture("resources/switchSay.png");

	/*sprite = new Sprite();
	sprite->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	worldTransform_Sprite.Initialize();*/
	
	//
	//
	//リソースを作る
	//テクスチャ

	/*Texture = textureManager_->LoadTexture("resources/uvChecker.png");*/
	//サウンド
	//
	viewProjection_.Initialize();
	worldTransform_.Initialize();
}

void GamePlayState::Update()
{
#ifdef _DEBUG
	if (input->IspushKey(DIK_LALT)) {
		camera_->DebugCamera(true);
	}
	else {
		camera_->DebugCamera(false);
	}
#endif // _DEBUG

#pragma region GameCamera
	gameCamera_->Update();
	viewProjection_.translation_ = gameCamera_->GetViewProjection()->translation_;
	viewProjection_.rotation_ = gameCamera_->GetViewProjection()->rotation_;
#pragma endregion

	viewProjection_.UpdateMatrix();
	camera_->Update();
	player->Update();

	ground->Update();
	switch_->Update();

	input->GetJoystickState(0, JoyState);

	enemys_.remove_if([&](Enemy* enemy) {
		if (enemy->isDead()) {
			enemyCount -= 1;
			delete enemy;
			return true;
		}
		return false;
		});
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	for (Wall* wall : walls_) {
		wall->Update();
	}

	//Collision
	collisionManager_->ClearCollider();

	collisionManager_->AddCollider(player);
	collisionManager_->AddCollider(switch_);

	for (Wall* wall : walls_) {
		collisionManager_->AddCollider(wall);
	}
	for (Enemy* enemy : enemys_) {
		collisionManager_->AddCollider(enemy);
	}
	for (Bomb* pBomb : player->GetBombs()) {
		collisionManager_->AddCollider(pBomb);
	}

	collisionManager_->CheckAllCollisions();

	if (enemyCount <= 0 && gameoverTimer == 0) {
		clearTimer++;
	}
	else if (enemyCountMax > enemyCount && enemyCount > 0) {
		gameoverTimer++;
	}
	else if (player->GetIsDead()) {
		gameoverTimer += 40;
	}
	else {
		clearTimer = 0;
		gameoverTimer = 0;
	}

	if (clearTimer >= 90) {
		EnemySpawn(Vector3(8, -1, 2), 0, Vector3{ 0.0f,0.0f,0.0f });

		EnemySpawn(Vector3(-10, -1, 0), 0, Vector3{ 0.0f,0.0f,0.0f });

		EnemySpawn(Vector3(-12, -1, 16), 0, Vector3{ 0.0f,0.0f,0.0f });
		player->Reset();
		StateNo = 5;//StageClear
		clearTimer = 0;
	}

	if (gameoverTimer >= 90) {
		for (Enemy* enemy : enemys_) {
			enemy->SetDead(true);
		}

		EnemySpawn(Vector3(8, -1, 2), 0, Vector3{ 0.0f,0.0f,0.0f });

		EnemySpawn(Vector3(-10, -1, 0), 0, Vector3{ 0.0f,0.0f,0.0f });

		EnemySpawn(Vector3(-12, -1, 16), 0, Vector3{ 0.0f,0.0f,0.0f });
		player->Reset();
		StateNo = 6;//GameOver
		gameoverTimer = 0;
	}

	//2D

}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから

	//sphere->Draw(worldTransform_, viewProjection_, Texture);

	ground->Draw(viewProjection_);
	player->Draw(viewProjection_);
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	for (Wall* wall : walls_) {
		wall->Draw(viewProjection_);
	}
	switch_->Draw(viewProjection_);
	//3Dモデル描画ここまで	


	//Sprite描画ここから

	enemySay->Draw(worldTransform_EnemySprite, enemySayTexture);
	playerSay->Draw(worldTransform_PlayerSprite, playerSayTexture);
	switchSay->Draw(worldTransform_Stage3Sprite, switchTexture);

	//sprite->Draw(worldTransform_Sprite, Texture);


	//Sprite描画ここまで

	//描画ここまで
}

void GamePlayState::EnemySpawn(const Vector3& position, int moveMode, Vector3 moveSpeed) {
	enemyCount += 1;
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel,moveMode,moveSpeed);
	enemy_->SetPosition(position);
	enemys_.push_back(enemy_);
}

void GamePlayState::WallSpawn(const Vector3& position) {
	wall_ = new Wall();
	wall_->Initialize(wallModel_);
	wall_->SetPosition(position);
	walls_.push_back(wall_);
}