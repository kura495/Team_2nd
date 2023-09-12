#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "Input.h"
#include "VectorCalc.h"
#include "Base/Math/MatrixCalc.h"

#include "GameObject/Bomb/Bomb.h"
#include "GameObject/Wall/Wall.h"
#include "GameObject/Switch/Switch.h"

class Player :public Collider
{
public:
	void Initialize(Model* explotionModel, Model* bombModel);
	void Update();
	void Draw(const ViewProjection& viewProjection);


	void SetWall(Wall* walls) { walls_.push_back(walls); }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>爆弾のリスト</returns>
	const std::list<Bomb*>& GetBombs() const { return bombs_; }

	Vector3 GetWorldPosition() override;
	void OnCollision(const uint32_t& Attribute)override;

	void SetPosition(Vector3 position) { worldTransform_.translation_ = position; }

	/// <summary>
	/// ゲームのループが終わった時に元に戻したい処理
	/// </summary>
	void Reset();

private:
	void ApplyGlobalVariables();
	void ImGui();

	Vector3 CollisionDirection();

	/// <summary>
	/// 爆弾の処理
	/// </summary>
	void Attack();

	float Lerp(const float& a, const float& b, float t);
	float LerpShortAngle(float a, float b, float t);

	Input* input = nullptr;
	Model* model = nullptr;
	Model* explotionModel_ = {};
	Model* bombModel_ = {};
	GlobalVariables* globalVariables = nullptr;
	WorldTransform worldTransform_;
	float speed = 0.0f;

	XINPUT_STATE joyState;

	//Bomb* bomb_ = nullptr;	//爆弾

	std::list<Bomb*>bombs_;	//爆弾
	std::list<Wall*> walls_;
	Bomb* newBomb;


	bool isMove = false;	//プレイヤーが移動しているか　false:移動していない
	bool xButtonPressed = false;	//xボタンを押したか	//false : 押していない
	bool isTouchObject = false;	//プレイヤーが他オブジェクトと接触しているか	//false : 接触していない

	Vector3 collisionDirection;	//当たった方向

	const float threshold = 0.7f;	//しきい値
	float angle_;	//目標角度

	const int MaxBomb_ = 5;
	int BombNum_ = 0;
	Vector3 direction;

	Vector3 move;

};

