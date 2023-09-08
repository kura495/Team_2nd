#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "Input.h"
#include "VectorCalc.h"
#include "Base/Math/MatrixCalc.h"

class Player
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	void ApplyGlobalVariables();
	void ImGui();

	float Lerp(const float& a, const float& b, float t);
	float LerpShortAngle(float a, float b, float t);

	Input* input = nullptr;
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	WorldTransform worldTransform_;
	float speed = 0.0f;
	XINPUT_STATE joyState;

	bool isMove = false;	//プレイヤーが移動しているか　false:移動していない
	const float threshold = 0.7f;	//しきい値
	float angle_;	//目標角度
};

