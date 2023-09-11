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
	collisionManagerPlayer_ = new CollisionManager();
	//
	//3Dオブジェクト生成



	model = Model::CreateModelFromObj("resources", "bunny.obj");
	bombModel_ = Model::CreateModelFromObj("resources", "Bomb.obj");
	explosionModel_ = Model::CreateModelFromObj("resources", "ExplosionBomb.obj");
	enemyModel = Model::CreateModelFromObj("resources", "enemy.obj");
	wallModel_ = Model::CreateModelFromObj("resources", "cube.obj");
	groundModel = Model::CreateModelFromObj("resources", "ground.obj");

	
	WallSpawn(Vector3(6, 0, 0));
	WallSpawn(Vector3(6, 0, 2));

	WallSpawn(Vector3(-5, 0, 0));
	WallSpawn(Vector3(-5, 0, 2));


	player = new Player();
	player->Initialize(explosionModel_, bombModel_,wall_);
	sphere = new Sphere();
	sphere->Initialize();
	ground = new Ground();
	ground->Initialize(groundModel);
	switch_ = new Switch();
	switch_->Initialize(model, Vector3(0, 0, 0));

	EnemySpawn(Vector3(10, -1, 0));

	EnemySpawn(Vector3(20, -1, 12));

	EnemySpawn(Vector3(-12, -1, -10));
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
	switch_->Update(player);

	input->GetJoystickState(0, JoyState);

	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->isDead()) {
			delete enemy;
			return true;
		}
		return false;
		});
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	
	for(Wall* wall : walls_) {
		wall->Update();
	}

	//Collision
	collisionManager_->ClearCollider();
	collisionManagerPlayer_->ClearCollider();

	collisionManagerPlayer_->AddCollider(player);
	

	for (Wall* wall : walls_) {
		collisionManagerPlayer_->AddCollider(wall);
	}

	for (Enemy* enemy : enemys_) {
		collisionManager_->AddCollider(enemy);
	}
	for (Bomb* pBomb : player->GetBombs()) {
		collisionManager_->AddCollider(pBomb);
	}

	collisionManager_->CheckAllCollisions();
	collisionManagerPlayer_->CheckAllCollisions();

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
	ImGui::End();
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

	//sprite->Draw(worldTransform_Sprite, Texture);


	//Sprite描画ここまで

	//描画ここまで
}

void GamePlayState::EnemySpawn(const Vector3& position) {
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel);
	enemy_->SetPosition(position);
	enemys_.push_back(enemy_);
}

void GamePlayState::WallSpawn(const Vector3& position) {
	wall_ = new Wall();
	wall_->Initialize(wallModel_);
	wall_->SetPosition(position);
	walls_.push_back(wall_);
}