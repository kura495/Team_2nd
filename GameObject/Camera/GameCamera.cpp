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
	viewProjection_.UpdateMatrix();
}
