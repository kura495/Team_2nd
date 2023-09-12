#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "Input.h"
#include "VectorCalc.h"
#include "Base/Math/MatrixCalc.h"

#include "GameObject/Bomb/Bomb.h"

class Player : public Collider
{
public:
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition()override;
	void OnCollision(const uint32_t& collisionAttribute)override;
	const std::list<Bomb*>& GetBombs() const { return bombs_; }
private:
	void ApplyGlobalVariables();
	void ImGui();

	/// <summary>
	/// 爆弾の処理
	/// </summary>
	void Attack();

	float Lerp(const float& a, const float& b, float t);
	float LerpShortAngle(float a, float b, float t);

	Input* input = nullptr;
	Model* model = nullptr;
	GlobalVariables* globalVariables = nullptr;
	WorldTransform worldTransform_;
	float speed = 0.0f;
	XINPUT_STATE joyState;

	//Bomb* bomb_ = nullptr;	//爆弾

	std::list<Bomb*>bombs_;	//爆弾
	Bomb* newBomb;

	bool isMove = false;	//プレイヤーが移動しているか　false:移動していない
	const float threshold = 0.7f;	//しきい値
	float angle_;	//目標角度
};

