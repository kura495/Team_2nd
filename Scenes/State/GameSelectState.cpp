#include"Scenes/State/GameSelectState.h"

void GameSelectState::Initialize()
{
	textureManager_ = TextureManager::GetInstance();

	stage1 = new Sprite();
	stage1->Initialize(Stage1SpriteLeftTop[0], Stage1SpriteLeftBottom[0], Stage1SpriteRightTop[1], Stage1SpriteRightBottom[1]);
	worldTransform_Stage1Sprite.Initialize();
	stage1Tex = textureManager_->LoadTexture("resources/Stage1.png");

	stage2 = new Sprite();
	stage2->Initialize(Stage2SpriteLeftTop[0], Stage2SpriteLeftBottom[0], Stage2SpriteRightTop[1], Stage2SpriteRightBottom[1]);
	worldTransform_Stage2Sprite.Initialize();
	stage2Tex = textureManager_->LoadTexture("resources/Stage2.png");

	stage3 = new Sprite();
	stage3->Initialize(Stage3SpriteLeftTop[0], Stage3SpriteLeftBottom[0], Stage3SpriteRightTop[1], Stage3SpriteRightBottom[1]);
	worldTransform_Stage3Sprite.Initialize();
	stage3Tex = textureManager_->LoadTexture("resources/Stage3.png");

	worldTransform_Stage1Sprite.translation_ = { 30.0f,0.0f,0.0f };
	worldTransform_Stage2Sprite.translation_ = { 600.0f,100.0f,0.0f };
	worldTransform_Stage3Sprite.translation_ = { -300.0f,100.0f,0.0f };
	worldTransform_Stage1Sprite.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_Stage2Sprite.scale_ = { 0.8f,0.8f,1.0f };
	worldTransform_Stage3Sprite.scale_ = { 0.8f,0.8f,1.0f };

	sprite = new Sprite();
	sprite->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	worldTransform_Sprite.Initialize();
	TextureS1 = textureManager_->LoadTexture("resources/background.png");
	TextureS2 = textureManager_->LoadTexture("resources/background.png");
	TextureS3 = textureManager_->LoadTexture("resources/background.png");

	selectStageNo = 1;
}

void GameSelectState::Update()
{
	ImGui::Begin("Info");
	ImGui::SliderInt("SelectStageNo", &selectStageNo, 1, 3);
	ImGui::Text("StageSelect : LeftJoyStick");
	ImGui::Text("ReturnStage : X Button");
	ImGui::Text("%d", stickTimer);
	ImGui::End();

	ImGui::Begin("Sprite");
	ImGui::SliderFloat3("Sprite1", &worldTransform_Stage1Sprite.translation_.x, -1280, 1280);
	ImGui::SliderFloat3("Sprite2", &worldTransform_Stage2Sprite.translation_.x, -1280, 1280);
	ImGui::SliderFloat3("Sprite3", &worldTransform_Stage3Sprite.translation_.x, -1280, 1280);
	ImGui::End();

	worldTransform_Stage1Sprite.UpdateMatrix();
	worldTransform_Stage2Sprite.UpdateMatrix();
	worldTransform_Stage3Sprite.UpdateMatrix();

	Input::GetInstance()->GetJoystickState(0, joyState);
	if (Input::GetInstance()->IsTreggerKey(DIK_A)) {
		
		if (selectStageNo < 2) {
			selectStageNo = 3;
		}
		else {
			selectStageNo -= 1;
		}
	}
	else if (Input::GetInstance()->IsTreggerKey(DIK_D)) {
		if (selectStageNo > 2) {
			selectStageNo = 1;
		}
		else {
			selectStageNo += 1;
		}
	}

	if (joyState.Gamepad.sThumbLX != 0 ||joyState.Gamepad.sThumbLY != 0) {

		//StageSelect
		if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX >threshold)
		{
			stickTimer--;
			if (stickTimer <= 0) {
				if (selectStageNo > 2) {
					selectStageNo = 1;
					stickTimer = 10;
				}
				else {
					selectStageNo += 1;
					stickTimer = 10;
				}
			}
		}
		else {
			stickTimer--;
			if (stickTimer <= 0) {
				if (selectStageNo < 2) {
					selectStageNo = 3;
					stickTimer = 10;
				}
				else {
					selectStageNo -= 1;
					stickTimer = 10;
				}
			}
		}
		
	}
	else {
		stickTimer = 5;
	}
	if (selectStageNo == 1) {
		worldTransform_Stage1Sprite.translation_ = { 30.0f,0.0f,0.0f };
		worldTransform_Stage2Sprite.translation_ = { 600.0f,100.0f,0.0f };
		worldTransform_Stage3Sprite.translation_ = { -300.0f,100.0f,0.0f };
		worldTransform_Stage1Sprite.scale_ = { 1.0f,1.0f,1.0f };
		worldTransform_Stage2Sprite.scale_ = { 0.8f,0.8f,1.0f };
		worldTransform_Stage3Sprite.scale_ = { 0.8f,0.8f,1.0f };
	}
	else if (selectStageNo == 2) {
		worldTransform_Stage1Sprite.translation_ = { -300.0f,100.0f,0.0f };
		worldTransform_Stage2Sprite.translation_ = { 30.0f,0.0f,0.0f };
		worldTransform_Stage3Sprite.translation_ = { 600.0f,100.0f,0.0f };
		worldTransform_Stage1Sprite.scale_ = { 0.8f,0.8f,1.0f };
		worldTransform_Stage2Sprite.scale_ = { 1.0f,1.0f,1.0f };
		worldTransform_Stage3Sprite.scale_ = { 0.8f,0.8f,1.0f };
	}
	else if (selectStageNo == 3) {
		worldTransform_Stage1Sprite.translation_ = { 600.0f,100.0f,0.0f };
		worldTransform_Stage2Sprite.translation_ = { -300.0f,100.0f,0.0f };
		worldTransform_Stage3Sprite.translation_ = { 30.0f,0.0f,0.0f };
		worldTransform_Stage1Sprite.scale_ = { 0.8f,0.8f,1.0f };
		worldTransform_Stage2Sprite.scale_ = { 0.8f,0.8f,1.0f };
		worldTransform_Stage3Sprite.scale_ = { 1.0f,1.0f,1.0f };
	}
	//DecisionStage
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A||Input::GetInstance()->IsTreggerKey(DIK_SPACE))
	{
		if (!aButtonPressed)
		{
			StateNo = selectStageNo + 1;

			aButtonPressed = true;

		}
	}
	else
	{
		aButtonPressed = false;
	}
}

void GameSelectState::Draw()
{
	if (selectStageNo == 1) {
		sprite->Draw(worldTransform_Sprite, TextureS1);
	}
	if (selectStageNo == 2) {
		sprite->Draw(worldTransform_Sprite, TextureS2);
	}
	if (selectStageNo == 3) {
		sprite->Draw(worldTransform_Sprite, TextureS3);
	}

	stage1->Draw(worldTransform_Stage1Sprite, stage1Tex);
	stage2->Draw(worldTransform_Stage2Sprite, stage2Tex);
	stage3->Draw(worldTransform_Stage3Sprite, stage3Tex);
}
