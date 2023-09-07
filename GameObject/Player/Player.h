#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "Input.h"
#include "VectorCalc.h"

class Player
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	void ApplyGlobalVariables();
	void ImGui();

	Input* input = nullptr;
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	WorldTransform worldTransform_;
	float speed = 0.0f;
	XINPUT_STATE joyState;
};

