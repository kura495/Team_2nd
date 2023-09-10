#include "GameCamera.h"

GameCamera::GameCamera(){}
GameCamera::~GameCamera(){}

void GameCamera::Initalize()
{
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0, 50,0 };
	viewProjection_.rotation_.x = {1.5};
}

void GameCamera::Update()
{
	ImGui::Begin("GameCamera");
	ImGui::SliderFloat("rotation",&viewProjection_.rotation_.x,-20,20);
	ImGui::SliderFloat3("rotation",&viewProjection_.translation_.x,-20,20);
	ImGui::End();
	viewProjection_.UpdateMatrix();
}
