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

	Model* bombModel_;
	Model* explosionModel_;

	model = Model::CreateModelFromObj("resources", "bunny.obj");

	bombModel_ = Model::CreateModelFromObj("resources", "Bomb.obj");
	explosionModel_ = Model::CreateModelFromObj("resources", "ExplosionBomb.obj");


	player = new Player();
	player->Initialize(explosionModel_, bombModel_);
	sphere = new Sphere();
	sphere->Initialize();
	wall = new Wall();
	wall->Initialize();

	EnemySpawn(Vector3(10, 0, 0));
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
	wall->Update();

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

	//Collision
	collisionManager_->ClearCollider();

	collisionManager_->AddCollider(player);
	collisionManager_->AddCollider(wall);

	for (Enemy* enemy : enemys_) {
		collisionManager_->AddCollider(enemy);
	}
	for (Bomb* pBomb : player->GetBombs()) {
		collisionManager_->AddCollider(pBomb);
	}

	collisionManager_->CheckAllCollisions();

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
	wall->Draw(viewProjection_);
	player->Draw(viewProjection_);
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	//3Dモデル描画ここまで	


	//Sprite描画ここから

	//sprite->Draw(worldTransform_Sprite, Texture);


	//Sprite描画ここまで

	//描画ここまで
}

void GamePlayState::EnemySpawn(const Vector3& position) {
	Enemy* enemy_ = new Enemy();
	enemy_->Initialize();
	enemy_->SetPosition(position);
	enemys_.push_back(enemy_);
}