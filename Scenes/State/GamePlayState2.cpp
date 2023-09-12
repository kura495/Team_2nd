#include "Scenes/State/GamePlayState2.h"

void GamePlayState2::Initialize()
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


	WallSpawn(Vector3(-35, 0, -8));
	WallSpawn(Vector3(-33, 0, -8));
	WallSpawn(Vector3(-31, 0, -8));
	WallSpawn(Vector3(-29, 0, -8));

	WallSpawn(Vector3(-29, 0, -10));
	WallSpawn(Vector3(-29, 0, -12));

	WallSpawn(Vector3(-25, 0, 4));
	WallSpawn(Vector3(-23, 0, 4));
	WallSpawn(Vector3(-21, 0, 4));
	WallSpawn(Vector3(-19, 0, 4));
	WallSpawn(Vector3(-17, 0, 4));


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
	switch_->Initialize(switchModel_, Vector3(0, 0, 0));


	EnemySpawn(Vector3(-20, 0, -12));
	EnemySpawn(Vector3(-31, 0, -4));
	EnemySpawn(Vector3(-21, 0, 7));
	EnemySpawn(Vector3(0, 0, 14));
	EnemySpawn(Vector3(-5, 0, 0));
	EnemySpawn(Vector3(-5, 0, -14));


	enemyCountMax = enemyCount;


	//
	//2Dオブジェクト作成
	sprite = new Sprite();
	sprite->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	worldTransform_Sprite.Initialize();
	//
	//
	//リソースを作る
	//テクスチャ
	Texture = textureManager_->LoadTexture("resources/uvChecker.png");
	//サウンド
	mokugyo = audio->LoadAudio("resources/mokugyo.wav");
	//
	viewProjection_.Initialize();
	worldTransform_.Initialize();
}

void GamePlayState2::Update()
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



	GlobalVariables::GetInstance()->Update();

	ImGui::Begin("Sound");
	ImGui::SliderInt("Pan", &Pan, 1, -1);
	ImGui::SliderFloat("Volume", &Volume, 0.0f, 1.0f);
	audio->Play(mokugyo, Volume, Pan);
	ImGui::End();
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("transform", &viewProjection_.translation_.x, 10.0f, -10.0f);
	audio->Play(mokugyo, Volume, Pan);
	ImGui::End();
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
	else {
		clearTimer = 0;
		gameoverTimer = 0;
	}

	if (clearTimer >= 90) {


		EnemySpawn(Vector3(-20, 0, -12));
		EnemySpawn(Vector3(-31, 0, -4));
		EnemySpawn(Vector3(-21, 0, 7));
		EnemySpawn(Vector3(0, 0, 14));
		EnemySpawn(Vector3(-5, 0, 0));
		EnemySpawn(Vector3(-5, 0, -14));

		StateNo = 5;//StageClear
	}

	if (gameoverTimer >= 90) {
		for (Enemy* enemy : enemys_) {
			enemy->SetDead(true);
		}


		EnemySpawn(Vector3(-20, 0, -12));
		EnemySpawn(Vector3(-31, 0, -4));
		EnemySpawn(Vector3(-21, 0, 7));
		EnemySpawn(Vector3(0, 0, 14));
		EnemySpawn(Vector3(-5, 0, 0));
		EnemySpawn(Vector3(-5, 0, -14));


		StateNo = 6;//GameOver
	}

	ImGui::Begin("System");
	if (input->PushAButton(JoyState)) {
		ImGui::Text("IsPushA");
	}
	if (input->PushBButton(JoyState)) {
		ImGui::Text("IsPushB");
	}
	if (input->PushXButton(JoyState)) {
		ImGui::Text("IsPushX");
	}
	if (input->PushYButton(JoyState)) {
		ImGui::Text("IsPushY");
	}
	ImGui::Text("enemyCount %d", enemyCount);
	ImGui::End();
}

void GamePlayState2::Draw()
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

	//sprite->Draw(worldTransform_Sprite, Texture);


	//Sprite描画ここまで

	//描画ここまで
}

void GamePlayState2::EnemySpawn(const Vector3& position) {
	enemyCount += 1;
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel);
	enemy_->SetPosition(position);
	enemys_.push_back(enemy_);
}

void GamePlayState2::WallSpawn(const Vector3& position) {
	wall_ = new Wall();
	wall_->Initialize(wallModel_);
	wall_->SetPosition(position);
	walls_.push_back(wall_);
}