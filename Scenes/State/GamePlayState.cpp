#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	DirectX_ = DirectXCommon::GetInstance();
	collisionManager_ = new CollisionManager();
	//
	//3Dオブジェクト生成
	player = new Player();
	player->Initialize();
	sphere = new Sphere();
	sphere->Initialize();

	EnemySpawn(Vector3(10, 10, 0));
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

	for (Enemy* enemy : enemys_) {
		collisionManager_->AddCollider(enemy);
	}
	/*for (Bomb* pBomb : player->GetBombs) {
		collisionManager_->AddCollider(pBomb);
	}*/
	//下のをPlayer.hで追加した後、上のコメントアウトを外したら動く
	//const std::list<Bomb*>& GetBombs() const { return bombs_; }

	collisionManager_->CheckAllCollisions();

	Input::GetInstance()->GetJoystickState(0, JoyState);
	ImGui::Begin("System");
	if (Input::GetInstance()->IsPushLSHOULDER(JoyState)) {
		ImGui::Text("IsPushLB");
	}
	if (Input::GetInstance()->IsPushRSHOULDER(JoyState)) {
		ImGui::Text("IsPushRB");
	}
	ImGui::End();
}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	sphere->Draw(worldTransform_, viewProjection_, Texture);
	player->Draw(viewProjection_);
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	//3Dモデル描画ここまで	


	//Sprite描画ここから
	sprite->Draw(worldTransform_Sprite, Texture);


	//Sprite描画ここまで

	//描画ここまで
}

void GamePlayState::EnemySpawn(const Vector3& position) {
	Enemy* enemy_ = new Enemy();
	enemy_->Initialize();
	enemy_->SetPosition(position);
	enemys_.push_back(enemy_);
}